#pragma once

typedef int Servo;

typedef struct Pulse Pulse;
struct Pulse
{
	Servo SERVO;
	int LENGTH;
	int NUMBER;
};
