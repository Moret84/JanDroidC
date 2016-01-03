#pragma once

#include <socket.h>
#include <Motor.h>
#include <Servo.h>

typedef struct JandroidStuff JandroidStuff;
struct JandroidStuff
{
	Motor* motors;
	Servo* servos;
	Socket socket, client_socket;
};
