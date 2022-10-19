//Funcionamiento básico de puente H

/*
  Para que funcione, la arduino debe estar conectada a algún equipo. En caso de querer automatizarlo,
  se recomoienda conectar un cable en el conector entrada/salida de 5v del puente h (tercer conector con tornilo)
*/
int entrada1 = 7;
int entrada2 = 8;
int entrada3 = 9;
int entrada4 = 10;

void setup() {
  pinMode(entrada1, OUTPUT);
  pinMode(entrada2, OUTPUT);
  pinMode(entrada3, OUTPUT);
  pinMode(entrada4, OUTPUT);
}

void loop() {
  digitalWrite(entrada1, HIGH);
  digitalWrite(entrada2, LOW);
  digitalWrite(entrada3, HIGH);
  digitalWrite(entrada4, LOW);
  delay(3000);
  digitalWrite(entrada1, LOW);
  digitalWrite(entrada2, HIGH);
  digitalWrite(entrada3, HIGH);
  digitalWrite(entrada4, LOW);
  delay(3000);
  digitalWrite(entrada1, HIGH);
  digitalWrite(entrada2, LOW);
  digitalWrite(entrada3, LOW);
  digitalWrite(entrada4, HIGH);
  delay(3000);
  digitalWrite(entrada1, LOW);
  digitalWrite(entrada2, LOW);
  digitalWrite(entrada3, LOW);
  digitalWrite(entrada4, LOW);
  delay(3000);
}
