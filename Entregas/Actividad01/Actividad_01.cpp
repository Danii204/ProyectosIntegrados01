/*Actividad 1*/

//Importacion de librerias
#include <LiquidCrystal.h>

//Configuramos pines de la LCD
LiquidCrystal lcd(A0, A1, 5, 4, 3, 2);  

//Pines Ultrasonidos
const int echo1=12;     //Echo Ultrasonidos 1
const int trigger1=13;  //Trigger Ultrasonidos 1
const int echo2=7;      //Echo Ultrasonidos 2
const int trigger2=8;   //Echo Ultrasonidos 2

//Pines Motores
int DA1 = 11; //Direccion A motor 1
int DB1 = 10; //Direccion B motor 1
int DA2 = 9;  //Direccion A motor 2
int DB2 = 6;  //Direccion B motor 2

//Variables que necesitaremos
int distF;  //Distancia hacia delante
int distB;  //Distancia hacia atras

void setup(){
    Serial.begin(9600);

    //LCD
    lcd.begin(16, 2);   //Indicamos resolucion 16x2 de la LCD
    lcd.clear();    //Limpiamos pantalla
    lcd.print("Daniel Acevedo");    //Impresion en la primera posicion
    lcd.setCursor(0, 1);    //Cambio del cursor a la segunda posicon
    lcd.print("Actividad 1");   //Impresion en la segunda posicion

    //Ultrasonidos 1
    pinMode(trigger1,OUTPUT);
    pinMode(echo1,INPUT);
    digitalWrite(trigger1,LOW);

    //Ultrasonidos 2
    pinMode(trigger2,OUTPUT);
    pinMode(echo2,INPUT);
    digitalWrite(trigger2,LOW);

    //Motor 1
    pinMode(DA1,OUTPUT);
    pinMode(DB1,OUTPUT);

    //Motor 2
    pinMode(DA2,OUTPUT);
    pinMode(DB2,OUTPUT);

}

int detecta_sensor1() { //Ultrasonidos 1
  long t;
  long d;
  digitalWrite(trigger1,LOW);
  delayMicroseconds(5);
  digitalWrite(trigger1,HIGH);
  delayMicroseconds(15);
  digitalWrite(trigger1,LOW);
  t=pulseIn(echo1,HIGH);
  d=t*0.01657;
  return (d);
}

int detecta_sensor2() { //Ultrasonidos 2
  long t;
  long d;
  digitalWrite(trigger2,LOW);
  delayMicroseconds(5);
  digitalWrite(trigger2,HIGH);
  delayMicroseconds(15);
  digitalWrite(trigger2,LOW);
  t=pulseIn(echo2,HIGH);
  d=t*0.01657;
  return (d);
}

void loop(){
  distF=detecta_sensor1();
  distB=detecta_sensor2();
  if (distF>distB && distF>30){ //Si distancia alante>disntacia atras --> Delante
    analogWrite(DA1,100);
    analogWrite(DB1,0);
    analogWrite(DA2,100);
    analogWrite(DB2,0);
  }
  if (distB>distF && distB>30){ //Si distancia de detras>distancia de alante --> Atras
    analogWrite(DA1,0);
    analogWrite(DB1,100);
    analogWrite(DA2,0);
    analogWrite(DB2,100);
  }
  if (distF<40 && distB<40){    //Si la distancia hacia delante y hacia atras es < 40 --> Paro
    analogWrite(DA1,0);
    analogWrite(DB1,0);
    analogWrite(DA2,0);
    analogWrite(DB2,0);
  }

  delay(500);   //Espero medio segundo
}