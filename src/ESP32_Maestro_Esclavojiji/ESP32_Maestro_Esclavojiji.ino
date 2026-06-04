#include <WiFi.h> //jeje no se puede usar xdxd
#include <esp_now.h> //
#include <Wire.h>
#include <Adafruit_VL53L0X.h> // libreria para usar los sensores VL53L0X

Adafruit_VL53L0X sensor = Adafruit_VL53L0X();

// este es el mac del receptpr 
uint8_t direccionReceptor[] = {
  0xF0, 0x24, 0xF9, 0x0C, 0x6C, 0x2C
};

// estructura de datos jejejeje
typedef struct {
  int distancia;
} Datos;

Datos datosEnviar;

void setup() {

  Serial.begin(115200);

  // I2C pipipipi
  Wire.begin(8, 9);

  // inicializar sensor 
  if (!sensor.begin()) {
    Serial.println("No se detecto VL53L0X"); //va a mandar "no se detecto VL53L0X"
    while (1);
  }

  Serial.println("VL53L0X listo"); // va a mandar esto cuando los sensores esten listos

  // wiFi modo estación 
  WiFi.mode(WIFI_STA);

  // inicializar ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error ESP-NOW");
    return;
  }

  // configurar receptor
  esp_now_peer_info_t peerInfo = {};

  memcpy(peerInfo.peer_addr,
         direccionReceptor,
         6);

  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // agregar receptor
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Error agregando peer");
    return;
  }

  Serial.println("Transmisor listo");
}

void loop() {

  VL53L0X_RangingMeasurementData_t medida;

  sensor.rangingTest(&medida, false);

  if (medida.RangeStatus != 4) {

    datosEnviar.distancia = medida.RangeMilliMeter;

    Serial.print("Distancia: ");
    Serial.print(datosEnviar.distancia);
    Serial.println(" mm");x

    esp_now_send(
      direccionReceptor,
      (uint8_t *) &datosEnviar,
      sizeof(datosEnviar)
    );
  }
  else {

    Serial.println("Fuera de rango");
  }

  delay(200);
}