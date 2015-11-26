#pragma once
#include <Motor.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <wiringPi.h>
#include <softPwm.h>

#define NBMOTOR 4

enum {AvD, AvG, ArG, ArD};
Motor* initMotors();
void initPins(Motor* motors);
void forward(Motor* motors);
void backward(Motor* motors);
void go(Motor* motors);
void stopAll(Motor* motors);
void speedUp(Motor* motors);
void speedDown(Motor* motors);
void stopMotor(Motor motor);
