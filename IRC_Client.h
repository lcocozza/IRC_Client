#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> /* gethostbyname */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft.c"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

void	arg(int argc, char **argv);
