#include <QTRSensors.h>
#include <Arduino.h>
#include <WiFi.h>
#include <server.h>
#include <motor.h>

Motor motor;
PrivateServer ser;

// Define PWM parameters
const int pwmFreq = 10000;       // Frequency of 5 kHz
const int pwmResolution = 8;    // 8-bit resolution (values range from 0 to 255)
const int pwmChannelA = 7;      // PWM channel for motor A
const int pwmChannelB = 6;      // PWM channel for motor B
const int pwmDutyCycle = 30;    // Duty cycle as a percentage (0-255 for 8-bit resolution)
const int pin2 = 2;
const int pwmChannelC = 2;
void setup() {
  // Configure the server and motor
  motor.initialize();
  ser.initialize();
  motor.setSensors();
  digitalWrite(motor.AIN1,HIGH);
  digitalWrite(motor.BIN1,HIGH);
 //digitalWrite(motor.AIN2,LOW);
 // digitalWrite(motor.BIN2,LOW);

   ledcSetup(pwmChannelA,pwmFreq, pwmResolution);
  // ledcSetup(pwmChannelB,pwmFreq, pwmResolution);
  // ledcSetup(pwmChannelC,pwmFreq,pwmResolution);
   
  // Przypisanie kanału PWM do pinu
 // ledcAttachPin(motor.B_PWM,pwmChannelB);
  ledcAttachPin(motor.A_PWM, pwmChannelA);
 // ledcAttachPin(pin2,pwmChannelC);

  ledcWrite(pwmChannelA,70);
  //ledcWrite(pwmChannelB,70);
  //ledcWrite(pwmChannelC,70);






}

void loop() {
 // ser.clients();
  // Update sensor readings
  motor.updateSensors();
}