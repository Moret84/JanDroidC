#pragma once

#include <Motor.h>
#include <Servo.h>

#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <softPwm.h>
#include <wiringPi.h>

#define NBMOTOR 4
#define NBSERVO 2
#define PULSE_WIDTH 20000

enum {AvD, AvG, ArG, ArD};
enum {horizontal, vertical};

Motor* initMotors(void);
Servo* initServos(void);
void launchPulse(Pulse* pulse);
void moveCamera(Servo* servos, int x, int y);
void go(Motor* motors);
void stopAll(Motor* motors);
void setBackward(Motor* motors);
void setForward(Motor* motors);
void setSpeed(Motor* motors, int AvDs, int ArDs, int AvGs, int ArGs);
void setMotors(Motor* motors, int x, int y);
void reset(Motor* motors);
