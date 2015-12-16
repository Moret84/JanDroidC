#pragma once
#include <stdbool.h>

typedef struct Motor Motor;
struct Motor
{
	int PWM;
	int IN1;
	int IN2;
	int speed;
	bool inverted;
};
