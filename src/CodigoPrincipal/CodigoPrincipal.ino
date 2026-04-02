#include <Servo.h>

 int trigPinI = 12; // este es el sensor de ultrasonico de la izquierda
 int echoPinI = 13; // lo mismo 

 int trigPinD = A0; // este es el sensor de centro de ultraasonico 
 int echoPinD = A1; // lo mismo 

 int trigPinC = A2; // este es el sensor de ultrasonico derecha 
 int echoPinC = A3; // lo mismo 

Servo miServo;
int pinServo = 3;

int distanciaLimite = 10;

long distanciaDerecha = 0;
long distanciaCentro = 0;
long distanciaIzquierda = 0;



void setup() {
  pinMode(trigPinI, OUTPUT); // declarar
  pinMode(echoPinI, INPUT);
  
  pinMode(trigPinD, OUTPUT);
  pinMode(echoPinD, INPUT);

  pinMode(trigPinC, OUTPUT);
  pinMode(echoPinC, INPUT);

  miServo.attach(pinServo);
  miServo.write(90);

  Serial.begin(115200); //velocidad
}

void loop() {

  // Medir distancias de cada ultrasonico
  distanciaDerecha = medirDistancia(trigPinD, echoPinD); // la informacion que se va a guardar
  distanciaCentro = medirDistancia(trigPinC, echoPinC);
  distanciaIzquierda = medirDistancia(trigPinI, echoPinI);

  Serial.print("Centro: ");
  Serial.println(distanciaCentro);

  if (distanciaCentro < 20 && distanciaCentro > 5) {
    miServo.write(0);
    delay(1000);
    miServo.write(70);
   // delay(5000);
  }

  delay(10); //
}


// Funcion 
long medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  
  long duracion = pulseIn(echoPin, HIGH, 30000);

 
  if (duracion == 0) { // duracion 
    return 0;
  }

  long distancia = duracion * 0.034 / 2;
  return distancia;
}