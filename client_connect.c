#include "header.h"

static void init(void)
{
#ifdef _WIN32
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(err < 0)
    {
        puts("WSAStartup failed !");
        exit(EXIT_FAILURE);
    }
#endif
}

static void end(void)
{
#ifdef _WIN32
    WSACleanup();
#endif
}

void	arg(int argc, char **argv)
{
	if (argc != 3)
	{
		printf(	"Invalide Argument.\n"
			"Usage: ./%s [ip] [port]\n", argv[0]);
		exit(0);
	}

}

int	init_connection(char **argv)
{
	int temps = 0;
	int network_socket;
	int connection_status;

	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN server_address = {0};
	struct hostent *hostinfo;

	if (network_socket == INVALID_SOCKET)
	{
		perror("socket()");
		closesocket(network_socket);
		exit(errno);
	}
	
	hostinfo = gethostbyname(argv[1]);
	if (hostinfo == NULL)
	{
		printf("Unknow host %s.\n", argv[1]);
		closesocket(network_socket);
		exit(EXIT_FAILURE);
	}
	else
		printf("Building connection...\n");

	server_address.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
	server_address.sin_port = htons(atoi(argv[2]));
	server_address.sin_family = AF_INET;
	
	do
	{
		printf("try to connect to the server...\n");
		connection_status = connect(network_socket, (SOCKADDR *) &server_address, sizeof(SOCKADDR));
		ATTENDRE(1);
		if (connection_status != SOCKET_ERROR)
			temps = 15;
		else
			temps++;

	} while (temps < 15);

	if (connection_status == SOCKET_ERROR)
	{	
		perror("connect()");
		closesocket(network_socket);
		exit(errno);
	}
	else
		printf("Success connecting.\n");
	
	return network_socket;
}

void	close_connection(int socket)
{
	closesocket(socket);
}