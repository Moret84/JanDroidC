#include <jandroid.h>

Motor* initMotors(int nbMotors)
{
	wiringPiSetup () ;
	Motor* motors = malloc(NBMOTOR * sizeof(Motor));

	motors[ArG].PWM = 0;
	motors[ArG].IN1 = 2;
	motors[ArG].IN2 = 3;
	motors[ArG].inverted = false;

	motors[ArD].PWM = 1;
	motors[ArD].IN1 = 4;
	motors[ArD].IN2 = 5;
	motors[ArD].inverted = true;

	motors[AvD].PWM = 12;
	motors[AvD].IN1 = 13;
	motors[AvD].IN2 = 14;
	motors[AvD].inverted = false;

	motors[AvG].PWM = 6;
	motors[AvG].IN1 = 10;
	motors[AvG].IN2 = 11;
	motors[AvG].inverted = true;

	return motors;
}

void initPins(Motor* motors)
{
	for(int i = AvD; i <= ArD; ++i)
	{
		pinMode(motors[i].PWM, OUTPUT);
		pinMode(motors[i].IN1, OUTPUT);
		pinMode(motors[i].IN2, OUTPUT);

		digitalWrite(motors[i].PWM, 0);
		digitalWrite(motors[i].IN1, 0);
		digitalWrite(motors[i].IN2, 0);
	}
}

void forward(Motor* motors)
{
	for(int i = AvD; i <= ArD; ++i)
	{
		digitalWrite(motors[i].PWM, 1);
		if(motors[i].inverted)
			digitalWrite(motors[i].IN1, 1);
		else
			digitalWrite(motors[i].IN2, 1);
	}
}

void stop(Motor* motors)
{
	for(int i = AvD; i <= ArD; ++i)
	{
		digitalWrite(motors[i].PWM, 0);
		digitalWrite(motors[i].IN1, 0);
		digitalWrite(motors[i].IN2, 0);
	}
}
