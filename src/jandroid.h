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
void go(Motor* motors);
void stopAll(Motor* motors);
void stopMotor(Motor motor);
void setBackward(Motor* motors);
void setForward(Motor* motors);
void setSpeed(Motor* motors, int AvDs, int ArDs, int AvGs, int ArGs);
void setMotors(Motor* motors, int x, int y);
void reset(Motor* motors);
