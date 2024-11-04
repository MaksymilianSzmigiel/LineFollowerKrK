#include "motor.h"
#include "Arduino.h"
#include "QTRSensors.h"

QTRSensors qtr;

const uint8_t  SensorCount = 8;
const uint8_t  sensorCount = 8;
const uint8_t values[] = {19, 18, 5, 17, 16, 4, 2, 15};

uint16_t sensorValues[SensorCount];


void Motor::initialize()
{
    pinMode(A_PWM, OUTPUT);
    pinMode(B_PWM, OUTPUT);
}

void Motor::setMotors()
{

  int motorSpeed = KP * error - KD * (error - previousError);
  previousError = error;

  int Mleft = M1 + motorSpeed;
  int Mright = M2 - motorSpeed;

  analogWrite(A_PWM, Mleft);
  analogWrite(A_PWM, Mright);
  

}

void Motor::setSensors() 
{
 qtr.setTypeRC();
  qtr.setSensorPins(values, sensorCount);

  Serial.begin(115200);
  delay(250);

  Serial.println("Calibrating...");
  for(int i = 0; i < 100; i++)
  {
   qtr.calibrate();
    delay(10);
  }
}

void Motor::updateSensors()
{
  unsigned int linePosition = qtr.readLineBlack(sensorValues, QTRReadMode::On);

 /*  for (uint8_t i = 0; i < sensorCount; i++) {
    Serial.print("Sensor ");
   Serial.print(i+1);
    Serial.print(": ");
    Serial.print(sensorValues[i]);
    Serial.print("  ");
    
  }*/
  
 Serial.print(linePosition);
  Serial.println();
  delay(1000);// Opóźnienie pomiędzy odczytami

}
