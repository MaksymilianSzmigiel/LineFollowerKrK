#include "motor.h"
#include "Arduino.h"

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
  

};
