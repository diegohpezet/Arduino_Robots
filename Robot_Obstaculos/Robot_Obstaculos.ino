#include <NewPing.h>

// Definición de variables y constantes relacionadas con el motor derecho, 
const int IN1 = 2;  
const int IN2 = 3;  
 
// Definición de variables y constantes relacionadas con el motor izquierdo
const int IN3 = 4;  
const int IN4 = 5;  

//ENA y ENB deberían estar en 120

// Definicion de variables y constantes relacionadas con el sensor de ultrasonido
const int trigger = 9;
const int echo = 10;
const int dist = 40;
NewPing sonar(trigger, echo, dist); //Se inicia el sensor de ultrasonidos
int cm;           //Variable para medir la distancia con el sensor de ultrasonidos
unsigned int uS;  //Variable para medir la distancia con el sensor de ultrasonidos

// Definición de variables y constantes relacionadas con los sensores IR
int lecturaSensorIzq; // Almacena el valor de la lectura del sensor izquierdo
int lecturaSensorDer; // Almacena el valor de la lectura del sensor derecho
const int sensorIzqPin = A1; // El sensor izq irá conectado al pin analógico A0
const int sensorDerPin = A0           ; // El sensor derecho irá conectado al pin analógico A1
 
void setup()
{
  // Se declaran todos los pines como salidas
  // Pines asociados a los motores
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  //Pines de los sensores IR
  pinMode( sensorIzqPin  , INPUT) ;
  pinMode( sensorDerPin  , INPUT) ;
  //Pines del sensor de ultrasonido
  pinMode(trigger,OUTPUT); 
  pinMode(echo,INPUT);   

  Serial.begin(9600); // Se inicia el puerto de comunicaciones en serie
  Serial.println("ROBOT PREPARADO...");
}
 
void loop()
{
  delay(50);      //Hacemos una pequeña pausa para estabilizar el programa
  lecturaSensores(); // Se lee el valor de los sensores IR
  // Se analiza el resultado de los sensores para hacer que el robot siga en el campo
 
  // Si el resultado de ambos sensores es 0 (zona blanca) el robot sigue se para
  if(lecturaSensorIzq == 0 || lecturaSensorDer == 0) {
    Evasion();
  }
  // Si ambos sensores retornan 0 (zona negra) el robot busca un obstáculo
  if (lecturaSensorIzq == 1 && lecturaSensorDer == 1) {
    if (cm != 0) {
      robotAvance();
    } else {
    robotDerecha(); // El robot avanza
   }
  }
}
/*
  Función lecturaSensorIR: leerá el valor del sensor de infrarrojos TCRT5000
  y lo almacena en una variable. Dicho sensor retornará el valor 0 (LOW) si
  el sensor está en zona blanca y el valor 1 (HIGH) si el sensor está en zona
  negra.
*/
void lecturaSensores()
{
  lecturaSensorIzq = digitalRead(sensorIzqPin); // Almacena la lectura del sensor izquierdo
  lecturaSensorDer = digitalRead(sensorDerPin); // Almacena la lectura del sensor derecho
 
  Serial.println("El valor del sensor izquierdo es ");
  Serial.println(lecturaSensorIzq);
 
  Serial.println("El valor del sensor derecho es ");
  Serial.println(lecturaSensorDer);

  uS = sonar.ping();
  cm = sonar.convert_cm(uS);

 
}
/*
  Función robotAvance: esta función hará que ambos motores se activen a máxima potencia
  por lo que el robot avanzará hacia delante
*/
void robotAvance()
{
  // Motor izquierdo
  // Al mantener un pin HIGH y el otro LOW el motor gira en un sentido
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
 
  // Motor derecho
  // Al mantener un pin HIGH y el otro LOW el motor gira en un sentido
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
}
/*
  Función robotRetroceso: esta función hará que ambos motores se activen a máxima potencia 
  en sentido contrario al anterior por lo que el robot avanzará hacia atrás
*/
void robotRetroceso()
{
  // Motor izquierdo
  // Al mantener un pin LOW y el otro HIGH el motor gira en sentido contrario al anterior
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
 
  // Motor derecho
  // Al mantener un pin LOW y el otro HIGH el motor gira en sentido contrario al anterior
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
}
 
/*
  Función robotDerecha: esta función acccionará el motor izquierdo y parará el derecho
  por lo que el coche girará hacia la derecha (sentido horario)
*/
void robotDerecha()
{
  //  Motor izquierdo
  // Se activa el motor izquierdo
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
 
  // Motor derecho
  // Se para el motor derecho
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
 
}
/*
  Función robotIzquierda: esta función acccionará el motor derecho y parará el izquierdo
  por lo que el coche girará hacia la izquierda (sentido antihorario)
*/
void robotIzquierda ()
{
   //  Motor izquierdo
  // Se para el motor izquierdo
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
 
  // Motor derecho
  // Se activa el motor derecho
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
}
/*
  Función robotParar: esta función parará ambos motores
  por lo que el robot se parará.
*/
void robotParar()
{
  // Motor izquierdo
  // Se para el motor izquierdo
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);
 
  // Motor derecho
  // Se para el motor derecho
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
 
}

void Evasion() {
  robotParar();
  delay(100);
  robotRetroceso();
  delay(1000);
}
