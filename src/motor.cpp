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

  Serial.println("Calibrating Sensors...");
  for(int i = 0; i < 100; i++)
  {
    qtr.calibrate();
    delay(50);
  }
}

void Motor::updateSensors()
{
  if(sensor_enabled)
  {
    int maxError = KP * 3500 + KD * 3500;
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

    float delta = KP * error + KD * (error - previousError);
    previousError = error;

    float percentError = (delta/maxError);

      int Mleft = M1 - percentError * 510 * (M1/M2);
      int Mright = M2 + percentError * 510 * (M2/M1);
      if(Mleft > 255)
        Mleft = 255;
      if(Mright > 255)
        Mright = 255;
      
        if(Mleft < 0)
          Mleft = 0;
        if(Mright < 0)
          Mright = 0;    
      
      if(Mleft >= 0 && Mright >= 0)
      {
        digitalWrite(AIN1,LOW);
        digitalWrite(BIN1,LOW);
        digitalWrite(AIN2,HIGH);
        digitalWrite(BIN2,HIGH);
      }  
      /*
      if(Mleft < 0)
      {
        Mleft = abs(Mleft);
        if(Mleft > 255)
          Mleft = 255;
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
      }
      if (Mright < 0)
      {
        Mright = abs(Mright);
        if(Mright > 255)
          Mright = 255;
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
      } 
      */
      analogWrite(A_PWM, Mleft);
      analogWrite(B_PWM, Mright);

  //  if(delta >1200)
  //   {
  //     int Mright = 55;
  //     int Mleft = 65;
  //     digitalWrite(AIN1,HIGH);
  //     digitalWrite(BIN1,LOW);
  //     digitalWrite(AIN2,LOW);
  //     digitalWrite(BIN2,HIGH);
  //     analogWrite(A_PWM, Mleft);
  //     analogWrite(B_PWM, Mright);                                                                                                                                                                                                                                                                                                
  //   }

  //   else if(delta < -1200)
  //   {
  //     int Mright = 55;
  //     int Mleft = 65;
  //     digitalWrite(AIN1,LOW);
  //     digitalWrite(BIN1,HIGH);
  //     digitalWrite(AIN2,HIGH);
  //     digitalWrite(BIN2,LOW);
  //     analogWrite(A_PWM, Mleft);
  //     analogWrite(B_PWM, Mright);
  //   }
    // else if((delta < 1200 && delta > 800) || (delta > -1200 && delta < -800))
    // {
    //   int Mleft = (delta/6) * (M3/M4);
    //   int Mright = (delta/6) * (M4/M3);
    //   if(Mleft > 255)
    //     Mleft = 255;
    //   if(Mright > 255)
    //     Mright = 255;
    //   if(Mleft < 0)
    //     Mleft = 0;
    //   if(Mright < 0)
    //     Mright = 0;
    //   digitalWrite(AIN1,LOW);
    //   digitalWrite(BIN1,LOW);
    //   digitalWrite(AIN2,HIGH);
    //   digitalWrite(BIN2,HIGH);
    //   analogWrite(A_PWM, Mleft);
    //   analogWrite(B_PWM, Mright);
    // }


    Serial.println();
    Serial.print("delta: ");
    Serial.print(delta);
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
    delay(20);// Opóźnienie pomiędzy odczytami
  } else 
  {
    analogWrite(A_PWM, 0);
    analogWrite(B_PWM, 0);
  }

}

