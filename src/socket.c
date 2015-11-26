#include <socket.h>

int init_socket()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);

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

char* receive_command(int socket, int buffer_size)
{
	char *command = malloc(buffer_size * sizeof(char));

	if((recv(socket, &command, sizeof(command), 0)) < 0)
	{
		perror("failed to receive");
		exit(errno);
	}

	return command;
}
