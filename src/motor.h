#pragma once

class Motor
{
public:
void setMotors();
void initialize();
private:

int KP = 0;
int KD = 0;
int error = 0;
int previousError = 0;
const int M1, M2 = 50;
const int A_PWM = 34;
const int B_PWM = 35;
const int AIN1 = 12;
const int AIN2 = 14;
const int BIN1 = 33;
const int BIN2 = 32;


};