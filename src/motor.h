#pragma once
#include <QTRSensors.h>
#include <Arduino.h>



class Motor
{
public:
void setMotors();
void initialize();
void setSensors();
void updateSensors();
void updateError();
const int AIN1 = 21;
const int BIN1 = 32;
const int AIN2 = 14;
const int BIN2 = 33;

String motorState;

float KP = 0.8;
float KD = 0.5;
int error = 0;
int previousError = 0;

const int M1 = 85;
const int M2 = 100;
const int M3 = 42;
const int M4 = 50;
const int A_PWM = 13;
const int B_PWM = 27;

private:

};