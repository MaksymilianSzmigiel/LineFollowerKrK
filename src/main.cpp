#include <QTRSensors.h>
#include <Arduino.h>
#include <WiFi.h>
#include <server.h>
#include <motor.h>

Motor motor;  
PrivateServer ser;

void setup() {
  // Konfiguracja czujników

 ser.initialize();
motor.setSensors();

}

void loop() {

  ser.clients();
  // Odczyt danych z czujników
 
  motor.updateSensors();
 
  
 
}
