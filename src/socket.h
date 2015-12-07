#pragma once

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close (s)
#define PORT 23

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

int init_socket();
int add_client(int socket);
char* receive_command(int socket, int buffer_size);