#include <socket.h>

Socket init_socket()
{
	Socket sock = socket(AF_INET, SOCK_STREAM, 0);
	char value = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));

	if(sock == INVALID_SOCKET)
	{
		perror("error creating socket");
		exit(errno);
	}

	sockaddr_in sin;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(23);

	if(bind(sock, (sockaddr*)&sin, sizeof(sin)) == INVALID_SOCKET)
	{
		perror("error binding socket");
		exit(errno);
	}

	if(listen(sock, 5) == SOCKET_ERROR)
	{
		perror("error listening");
		exit(errno);
	}

	return sock;
}

Socket add_client(Socket socket)
{
	sockaddr_in csin = { 0 };
	socklen_t size = sizeof(csin);

	int client_socket = accept(socket, (sockaddr*)&csin, &size);

	if(client_socket == INVALID_SOCKET)
	{
		perror("error accepting");
		exit(errno);
	}

	return client_socket;
}

void listen_command(Motor* motors, Servo* servos, Socket client_socket)
{
	int nb = 0, offset = 0;
	signed char command[3];

	while(1)
	{
		nb = recv(client_socket, &command[offset], sizeof(command) - offset, 0);
		offset += nb;
		if(nb == 0 || nb == -1)
		{
			shutdown(client_socket, SHUT_RDWR);
			closesocket(client_socket);
			return;
		}

		if(offset == 3)
		{
			switch(command[0])
			{
				case 'M':
					printf("Motor command received: x: %d, y: %d\n", command[1], command[2]);
					setMotors(motors, command[1], command[2]);
					break;
				case 'C':
					printf("Camera command received: x: %d, y: %d\n", command[1], command[2]);
					moveCamera(servos, command[1], command[2]);
					break;
			}

			offset = 0;
		}
	}
}
