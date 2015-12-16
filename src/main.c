#include <jandroid.h>
#include <socket.h>
#include <string.h>

int main()
{
	Motor* motors = initMotors();
	initPins(motors);

	Socket sock = init_socket(), csock;
	while((csock = add_client(sock)) > 0)
	{
		printf("%s\n", "Listening for command");

		listen_command(motors, csock);
	}
		closesocket(sock);
		free(motors);

		return 0;
}
