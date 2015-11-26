#include <jandroid.h>
#include <Command.h>
#include <socket.h>
#include <string.h>

int main()
{
	Motor* motors = initMotors();
	initPins(motors);

	Command* commands = initCommands();

	int sock = init_socket();
	int csock = add_client(sock);

	char command[10];
	printf("%s\n", "Listening for command");

	while((recv(csock, &command, sizeof(command), 0)) > 0)
	{
		printf("%s received\n", command);
		for(int i = 0; i < NBCOMMANDS; ++i)
		{
			if(strcmp(commands[i].name, command) == 0)
				commands[i].func(motors);
		}
	}

	closesocket(sock);
	closesocket(csock);
	free(motors);

	return 0;
}
