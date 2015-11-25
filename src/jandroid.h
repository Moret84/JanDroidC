#pragma once
#include <Motor.h>
#include <stdlib.h>
#include <wiringPi.h>

#define NBMOTOR 4

enum {AvD, AvG, ArG, ArD};
Motor* initMotors(int nbMotors);
void initPins(Motor* motors);
void forward(Motor* motors);
void stop(Motor* motors);
