#include <QTRSensors.h>
#include <Arduino.h>

QTRSensors qtr;

const uint8_t SensorCount = 8;
const uint8_t sensorCount = 8;

const uint8_t values[] = {23, 22, 21, 19, 5, 4, 2, 15};  // Piny czujników

uint16_t sensorValues[SensorCount];  // Przechowywanie odczytów z czujników

void setup() {
  // Konfiguracja czujników
  qtr.setTypeRC();
  qtr.setSensorPins(values, sensorCount);

  Serial.begin(9600);
  delay(250);
  pinMode(9, OUTPUT);
}

void loop() {
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
 digitalWrite(9, HIGH);
 delay(1000);
  digitalWrite(9, LOW);
delay(1000);
}
