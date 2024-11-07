#include "motor.h"
#include "Arduino.h"
#include "QTRSensors.h"

QTRSensors qtr;

const uint8_t  SensorCount = 8;
const uint8_t  sensorCount = 8;
const uint8_t values[] = {19, 18, 5, 17, 16, 4, 2, 15};

int MaxSilnik = 100;

uint16_t sensorValues[SensorCount];


void Motor::initialize()
{
    pinMode(A_PWM, OUTPUT);
    pinMode(B_PWM, OUTPUT);
    pinMode(AIN1,OUTPUT);
    pinMode(BIN1,OUTPUT);
    pinMode(AIN2,OUTPUT);
    pinMode(BIN2,OUTPUT);
}

void Motor::setMotors()
{

  
  
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
    delay(50);
  }
}

void Motor::updateSensors()
{
  unsigned int linePosition = qtr.readLineBlack(sensorValues, QTRReadMode::On);
  //qtr.read(sensorValues, QTRReadMode::On);

  error = linePosition - 3500;
  Serial.print("Error: ");
  Serial.print(error);
  Serial.println();


  // for (uint8_t i = 0; i < sensorCount; i++) {
  //   Serial.print("Sensor ");
  //   Serial.print(i+1);
  //   Serial.print(": ");
  //   Serial.print(sensorValues[i]);
  //   Serial.print("  ");
    
  // }

  Serial.print("Line position: ");
  Serial.print(linePosition);
  Serial.println();

  float motorSpeed = KP * error - KD * (error - previousError);
  previousError = error;


  if(motorSpeed > 0)
  {
    int Mleft = (M1 - motorSpeed/2)*(M1/M2);
    int Mright = M1 + motorSpeed/2;
    analogWrite(A_PWM, Mleft);
    analogWrite(B_PWM, Mright);
  }
  if(motorSpeed < 0)
  {
    int Mleft = (M1 + motorSpeed/2)*(M1/M2);
    int Mright = M1 - motorSpeed/2;
    analogWrite(A_PWM, Mleft);
    analogWrite(B_PWM, Mright);
  }
  if(motorSpeed == 0)
  {
    int Mleft = M1;
    int Mright = M2;
    analogWrite(A_PWM, Mleft);
    analogWrite(B_PWM, Mright);

  }



  

  Serial.println();
  Serial.print("motorSpeed: ");
  Serial.print(motorSpeed);
  Serial.println();
  /*
  Serial.println();
  Serial.print("LEFT MOTOR: ");
  Serial.print(Mleft);
  Serial.println();
  Serial.print("RIGHT MOTOR: ");
  Serial.print(Mright);
  Serial.println();
  */
  
  //Serial.print(linePosition);
  Serial.println();
  delay(100);// Opóźnienie pomiędzy odczytami

}
