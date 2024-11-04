#include <QTRSensors.h>
#include <Arduino.h>
#include <WiFi.h>
#include <server.h>

//QTRSensors qtr;

//const uint8_t SensorCount = 8;
//const uint8_t sensorCount = 8;

//const uint8_t values[] = {23, 22, 21, 19, 5, 4, 2, 15};  // Piny czujników

//uint16_t sensorValues[SensorCount];  // Przechowywanie odczytów z czujników

PrivateServer ser;

void setup() {
  // Konfiguracja czujników
 // qtr.setTypeRC();
 // qtr.setSensorPins(values, sensorCount);
 ser.initialize();
 // Serial.begin(9600);
 // delay(250);
 // pinMode(14, OUTPUT);

}

void loop() {

  ser.clients();
  // Odczyt danych z czujników
/*  qtr.read(sensorValues, QTRReadMode::On);

  // Wyświetlenie odczytanych wartości
 for (uint8_t i = 0; i < sensorCount; i++) {
    Serial.print("Sensor ");
   Serial.print(i);
    Serial.print(": ");
    Serial.print(sensorValues[i]);
    Serial.print("  ");
    
  }
  Serial.println();
  delay(1000);  // Opóźnienie pomiędzy odczytami
  */
 
}
