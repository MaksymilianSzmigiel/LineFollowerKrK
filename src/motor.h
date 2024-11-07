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

int KP = 1;
int KD = 1;
int error = 0;
int previousError = 0;

const int M1 = 50;
const int M2 = 50;
const int A_PWM = 13;
const int B_PWM = 27;

private:







};