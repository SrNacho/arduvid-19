#include <Servo.h>
Servo motor1; //objeto motor
int temp = 0; //temperatura
int Echo_der = 2; //pin del echo, sensor derecho
int Trigger_der = 3; //pin del trigger, sensor derecho
int Echo_izq = 4; //pin del echo, sensor izquierdo
int Trigger_izq = 5; //pin del trigger, sensor izquierdo
//int led = 6; //pin del led
int derecho = 0; //variable para contar cuando entran o salen
int izquierdo = 0; //variable para contar cuando entran o salen
int izquierdo_duracion, izquierdo_distancia;
int derecho_duracion, derecho_distancia;
int cuenta = 0;
String estado = "";


void setup() {
  motor1.attach(6);
  pinMode(Trigger_der, OUTPUT);
  pinMode(Echo_der, INPUT);
  pinMode(Trigger_izq, OUTPUT);
  pinMode(Echo_der, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void loop() {
  delay(100);
  temp = analogRead(1);
  temp = (temp - 102) / 2;
  //Serial.print("temperatura: ");
  //Serial.println(temp);
  digitalWrite(Trigger_der, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger_der, LOW);
  derecho_duracion = pulseIn(Echo_der, HIGH);
  derecho_distancia = (derecho_duracion / 2) / 29.1;

  digitalWrite(Trigger_izq, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger_izq, LOW);
  izquierdo_duracion = pulseIn(Echo_izq, HIGH);
  izquierdo_distancia = (izquierdo_duracion / 2) / 29.1;
  
  if (izquierdo_distancia < 50) { // Si esta a menos de 50 activa izquierdo.
    izquierdo = 1;
    
    //Serial.print("distancia izquierdo: ");
    //Serial.println(izquierdo_distancia);
  } else {
    izquierdo = 0;
  }
  if (derecho_distancia < 50) { // Si esta a menos de 50 activa derecho.
    derecho = 1;
    //Serial.print("distancia derecho: ");
    //Serial.println(derecho_distancia);
  } else {
    derecho = 0;
  }
  
  contador(izquierdo, derecho);

  if (cuenta >= 2 && temp >= 34) {
	motor1.write(360);
  	}else if(cuenta >3){
  	motor1.write(360);
   	}else if (cuenta <2) {
    motor1.write(0);
  }else if(cuenta >= 2 && temp <= 34){
  	motor1.write(0);
  }
  
}

void contador(int izquierdo, int derecho) {

  if (izquierdo == 1 && derecho == 0 && estado == "") {
    estado = "entrando";
    Serial.println(estado);
  }
  if (izquierdo == 1 && derecho == 1 && estado == "entrando") {
    estado = "entrando_mitad";
    Serial.println(estado);
  }
  if (izquierdo == 0 && derecho == 1 && estado == "entrando_mitad") {
    estado = "casi_entro";
    Serial.println(estado);
  }
  if (izquierdo == 0 && derecho == 0 && estado == "casi_entro") {
    estado = "";
    cuenta += 1;
    Serial.print("Cuenta uno mas: ");
    Serial.println(cuenta);
  }

  if (izquierdo == 0 && derecho == 1 && estado == "") {
    estado = "saliendo";
  }
  if (izquierdo == 1 && derecho == 1 && estado == "saliendo") {
    estado = "saliendo_mitad";
  }
  if (izquierdo == 1 && derecho == 0 && estado == "saliendo_mitad") {
    estado = "casi_salio";
  }
  if (izquierdo == 0 && derecho == 0 && estado == "casi_salio") {
    estado = "";
    cuenta -= 1;
    Serial.print("uno menos: ");
    Serial.println(cuenta);
  }

}