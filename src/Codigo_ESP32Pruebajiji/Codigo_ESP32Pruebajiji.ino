#include <ESP32Servo.h> // incluimos el esp32



#define TRIG_PIN 5 //pines de los sensores
#define ECHO_PIN 18 // pines de los sensores


#define ENA 1 //motor amarillo
#define IN1 2
#define IN2 4

#define ENB 7  // motor amarillo
#define IN3 6
#define IN4 8


#define SERVO_PIN 13 //pin deservo

Servo miServo;

void setup() {

  Serial.begin(115200);

  // ultrasonico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // motores
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // servo
  miServo.attach(SERVO_PIN);

  miServo.write(0);

 

  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.println("Carrito avanzando");
}

void loop() {



  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duracion = pulseIn(ECHO_PIN, HIGH);

  float distancia = duracion * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  

  if (distancia < 40) {

    Serial.println("Obstaculo detectado");

    miServo.write(90);

  } else {

    miServo.write(0);
  }

  delay(200);
}