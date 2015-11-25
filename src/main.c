
#include <jandroid.h>

int main()
{
	Motor* motors = initMotors(NBMOTOR);
	initPins(motors);

	forward(motors);
	delay(10000);
	stop(motors);

	return 0;
}
