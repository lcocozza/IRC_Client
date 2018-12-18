#ifdef _WIN32

#include <winsock2.h>
#include <windows.h>

#define ATTENDRE(temps) Sleep(temps*1000)

#elif __linux__

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
#define ATTENDRE(temps) sleep(temps)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#else

#error not defined for this platform

#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>

void	arg(int argc, char **argv);
int	init_connection(char **argv);
void	app(SOCKET socket);
void	send_message(SOCKET socket, char *buffer);
int	receive_message(SOCKET socket, char *buffer);
void	close_connection(SOCKET socket);
void	viderBuffer();
