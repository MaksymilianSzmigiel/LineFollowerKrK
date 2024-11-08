#include <QTRSensors.h>
#include <Arduino.h>
#include <WiFi.h>
#include <server.h>
#include <motor.h>

Motor motor;
PrivateServer ser;

void setup() {
  // Configure the server and motor
  motor.initialize();
  ser.initialize();
  motor.setSensors();
  digitalWrite(motor.AIN1,LOW);
  digitalWrite(motor.BIN1,LOW);
  digitalWrite(motor.AIN2,HIGH);
  digitalWrite(motor.BIN2,HIGH);

//    ledcSetup(pwmChannelA,pwmFreq, pwmResolution);
//    ledcSetup(pwmChannelB,pwmFreq, pwmResolution);
//   // ledcSetup(pwmChannelC,pwmFreq,pwmResolution);
   
//   // Przypisanie kanału PWM do pinu
//   ledcAttachPin(motor.B_PWM,pwmChannelB);
//   ledcAttachPin(motor.A_PWM, pwmChannelA);
//   ledcAttachPin(pin2,pwmChannelC);

//   ledcWrite(pwmChannelA,120);
//   ledcWrite(pwmChannelB,120);
//   //ledcWrite(pwmChannelC,70);

}

void loop() {
  motor.updateSensors();
 // motor.setMotors();
  delay(10);
 // ser.clients();
  // Update sensor readings

}