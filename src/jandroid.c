#include <jandroid.h>

Motor* initMotors()
{
	wiringPiSetup () ;
	Motor* motors = malloc(NBMOTOR * sizeof(Motor));

	motors[ArG].PWM = 0;
	motors[ArG].IN1 = 2;
	motors[ArG].IN2 = 3;
	motors[ArG].speed = 25;
	motors[ArG].inverted = false;

	motors[ArD].PWM = 1;
	motors[ArD].IN1 = 4;
	motors[ArD].IN2 = 5;
	motors[ArD].speed = 25;
	motors[ArD].inverted = true;

	motors[AvD].PWM = 12;
	motors[AvD].IN1 = 13;
	motors[AvD].IN2 = 14;
	motors[AvD].speed = 25;
	motors[AvD].inverted = false;

	motors[AvG].PWM = 6;
	motors[AvG].IN1 = 10;
	motors[AvG].IN2 = 11;
	motors[AvG].speed = 25;
	motors[AvG].inverted = true;

	return motors;
}

void initPins(Motor* motors)
{
	for(int i = AvD; i <= ArD; ++i)
	{
		if(softPwmCreate(motors[i].PWM, 0, 100) != 0)
			printf("%d\n", errno);

		pinMode(motors[i].IN1, OUTPUT);
		pinMode(motors[i].IN2, OUTPUT);

		digitalWrite(motors[i].IN1, 0);
		digitalWrite(motors[i].IN2, 0);
	}
}

void go(Motor* motors)
{
	for(int i = AvD; i <= ArD; ++i)
		softPwmWrite(motors[i].PWM, motors[i].speed);
}

void stopMotor(Motor motor)
{
	digitalWrite(motor.PWM, 0);
}

void stopAll(Motor* motors)
{
	for(int i = AvD; i <= ArD; ++i)
		stopMotor(motors[i]);
}

void reset(Motor* motors)
{
	for(int i = AvD; i <= ArD; ++i)
	{
		digitalWrite(motors[i].IN1, 0);
		digitalWrite(motors[i].IN2, 0);
	}
}

void setMotors(Motor* motors, int x, int y)
{
	if(y == 0)
	{
		reset(motors);
		stopAll(motors);
	}
	else
	{
		if(y > 0)
			setForward(motors);
		else
			setBackward(motors);

		int speed = abs(y); // y
		int shift = abs(x); // x

		if(x > 0)
			setSpeed(motors, speed - shift, speed - shift, speed, speed);
		else if (x < 0)
			setSpeed(motors, speed, speed, speed - shift, speed - shift);
		else
		setSpeed(motors, speed, speed, speed, speed);
	}
	go(motors);
}

void setSpeed(Motor* motors, int AvDs, int ArDs, int AvGs, int ArGs)
{
	motors[AvD].speed = AvDs;
	motors[ArD].speed = ArDs;
	motors[AvG].speed = AvGs;
	motors[ArG].speed = ArGs;
}

void setForward(Motor* motors)
{
	for(int i = AvD; i <= ArD; ++i)
	{
		if(motors[i].inverted)
			digitalWrite(motors[i].IN1, 1);
		else
			digitalWrite(motors[i].IN2, 1);
	}
}

void setBackward(Motor* motors)
{
	for(int i = AvD; i <= ArD; ++i)
	{
		if(motors[i].inverted)
			digitalWrite(motors[i].IN2, 1);
		else
			digitalWrite(motors[i].IN1, 1);
	}
}
