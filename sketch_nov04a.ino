/* Arduino Control Car V2  By: El Profe Garcia
 ARDUINO   L293D(Puente H)
 5          10
 6          15
 9          7
 10         2
 5V         1, 9, 16
 GND        4, 5, 12, 13

 El motor 1 se conecta a los pines 3 y 6 del Puente H
 El motor 2 se conecta a los pines 11 y 14 del Puente H

 La fuente de alimentacion de los Motores se conecta a tierra y
 el positivo al pin 8 del puente H.

 Conexion del Modulo Bluetooth HC-06 y el Arduino
 ARDUINO    Bluetooth HC-06
 0 (RX)       TX
 1 (TX)       RX
 5V           VCC
 GND          GND
 */
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3);      // Pol: ¡¡¡ATENCIO ALS PINS!!!

int izqA = 5;
int izqB = 6;             // Pol: no hem quadren tants pins... Asumeixo que funciona. Només serveixen per tirar enrere
int derA = 9;
int derB = 10;

int velocidad = 255;            // Velocidad de los motores (0-255)
int estado = 'c';         // inicia detenido

//Configurar bluetooth
char NOMBRE[21] = "ElPolLoPeta.RTFM.</3";
char BPS = '4';
char PASS[5] = "2345";

void setup()  {
  blue.begin(9600);
  // Serial.begin(9600);  /* Pol: Crec que no és necessari, ja que parlarem per uns altres ports amb bluetooth*/  // inicia el puerto serial para comunicacion con el Bluetooth
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);
  pinMode(13,OUTPUT);

  //Configurar bluetooth
  blue.print("AT");
  delay(1000);

  blue.print("AT+NAME");
  blue.print(NOMBRE);
  delay(1000);

  blue.print("AT+BAUD");
  blue.print(BPS);
  delay(1000);

  blue.print("AT+PIN");
  blue.print(PASS);
}

void loop()  {

  if(blue.available()>0) {        // lee el bluetooth y almacena en estado
    estado = blue.read();
  }

  switch (estado)
  {
    case 'a': // Boton desplazar al Frente
      analogWrite(derB, 0);
      analogWrite(izqB, 0);
      analogWrite(derA, velocidad);
      analogWrite(izqA, velocidad);
    case 'b': // Boton IZQ
      analogWrite(derB, 0);
      analogWrite(izqB, 0);
      analogWrite(derA, 0);
      analogWrite(izqA, velocidad);
    case 'c': // Boton Parar
      analogWrite(derB, 0);
      analogWrite(izqB, 0);
      analogWrite(derA, 0);
      analogWrite(izqA, 0);
    case 'd': // Boton DER
      analogWrite(derB, 0);
      analogWrite(izqB, 0);
      analogWrite(izqA, 0);
      analogWrite(derA, velocidad);
    case 'e': // Boton Reversa
      analogWrite(derA, 0);
      analogWrite(izqA, 0);
      analogWrite(derB, velocidad);
      analogWrite(izqB, velocidad);
    case 'h':                    // Tota aquesta secció sembla innecessària (els digitalWrite).
      digitalWrite(13, HIGH);    // Pol: Això hem sona a llumeta :3
    case 'm':
      digitalWrite(13, LOW);
    case 'i':
      digitalWrite(derB, HIGH);
    case 'n':
      digitalWrite(derB, LOW);
    case 'j':
      digitalWrite(derA, HIGH);
    case 'o':
      digitalWrite(derA, LOW);
    case 'k':
      digitalWrite(izqB, HIGH);
    case 'p':
      digitalWrite(izqB, HIGH);
    case 'l':
      digitalWrite(izqA, HIGH);
    case 'q':
      digitalWrite(izqA, HIGH);
    default:
      break;
    }
}
