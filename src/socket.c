#include <socket.h>

int init_socket()
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

int add_client(int socket)
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

void listen_command(Socket client_socket, Motor* motors)
{
	int nb = 0, offset = 0, x = 0, y = 0;
	signed char command[2];

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

		if(offset == 2)
		{
			x = command[0];
			y = command[1];
			printf("x: %d\n", x);
			printf("y: %d\n", y);
			setMotors(motors, x, y);
			offset = 0;
		}
	}
}
