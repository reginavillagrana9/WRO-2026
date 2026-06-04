#include <ESP32Servo.h> // incluimos el esp32

#define TRIG1 5 // los puertos
#define ECHO1 18 // puertos 

#define TRIG2 19 // puertos
#define ECHO2 21 //puertos

#define TRIG3 23 //puertos
#define ECHO3 36 //puertos

#define ENA 1 //para un motor amarillo 
#define IN1 2 // motor ena
#define IN2 4 // motor ena

#define ENB 7 // para motor amarillo
#define IN3 6 // motor enb
#define IN4 8 // motor enb

#define SERVO_PIN 13 //puerto de servo

float distancia1; // una variable que va a guardar valores con punto decimales 
float distancia2; // lo mismo 
float distancia3; // lo mismo 

Servo miServo;

float medirDistancia(int trigPin, int echoPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH, 25000);

  float distancia = duracion * 0.034 / 2;

  return distancia;
}

void setup() {

  Serial.begin(115200);

  pinMode(TRIG1, OUTPUT); //para los sensores
  pinMode(ECHO1, INPUT);

  pinMode(TRIG2, OUTPUT); //sensores
  pinMode(ECHO2, INPUT);

  pinMode(TRIG3, OUTPUT); //sensores
  pinMode(ECHO3, INPUT);

  pinMode(ENA, OUTPUT); //motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT); //motores
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  miServo.attach(SERVO_PIN);

  miServo.write(0);

  analogWrite(ENA, 100); // velocidad de motores
  analogWrite(ENB, 100); // velocidad de motores

  digitalWrite(IN1, HIGH); //que puerto de motor ena esta prendido y cual esta apagado 
  digitalWrite(IN2, LOW); // lo mismo 

  digitalWrite(IN3, HIGH); // que puerto de motor enb esta prendido y cual esta apagado
  digitalWrite(IN4, LOW); //lo mismo
}

void loop() {
  distancia1 = medirDistancia(TRIG1, ECHO1); //medimos la distancia y se guarda en la variable distancia1
  distancia2 = medirDistancia(TRIG2, ECHO2); //lo mismo
  distancia3 = medirDistancia(TRIG3, ECHO3); // lo mismo

  if (distancia1 < 10) {
    Serial.println("ACTIVA SENSOR 1");
    miServo.write(120);
}

  if (distancia2 < 70) {
    Serial.println("ACTIVA SENSOR 2");
    miServo.write(30);
}

  if (distancia3 < 10) {
    Serial.println("ACTIVA SENSOR 3");
    miServo.write(70);
  /*

  Serial.print("Sensor 1: ");
  Serial.print(distancia1);
  Serial.println(" cm");

  Serial.print("Sensor 2: ");
  Serial.print(distancia2);
  Serial.println(" cm");

  Serial.print("Sensor 3: ");
  Serial.print(distancia3);
  Serial.println(" cm");

 if (distancia1 < 10) {

  miServo.write(120);

}
else if (distancia2 < 70) {

  miServo.write(30);
  analogWrite(ENB, 200);

}
else if (distancia3 < 10) {

  miServo.write(30);

}
else {

  miServo.write(60);

}*/
}