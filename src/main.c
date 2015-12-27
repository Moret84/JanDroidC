#include <jandroid.h>
#include <signal.h>

JandroidStuff jandroid;

void cleanup(int num)
{
	closesocket(jandroid.client_socket);
	closesocket(jandroid.socket);
	free(jandroid.motors);
	free(jandroid.servos);
}

int main()
{
	signal(SIGINT, &cleanup);

	wiringPiSetup();

	jandroid.motors = initMotors();
	jandroid.servos = initServos();
	jandroid.socket = init_socket();

	while((jandroid.client_socket = add_client(jandroid.socket)) > 0)
	{
		printf("%s\n", "Listening for command");
		listen_command(jandroid.motors, jandroid.servos, jandroid.client_socket);
	}

	cleanup(0);
	return 0;
}
