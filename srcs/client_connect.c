#include "sys_incl.h"
#include "ft.h"

static void	init(void)
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

static void	end(void)
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
	SOCKET network_socket;
	int connection_status;
	int time = 0;

	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN server_address = {0};
	struct hostent *hostinfo = NULL;

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
		if (connection_status == SOCKET_ERROR)
			ATTENDRE(1);
		else
			time = 14;
		time++;
	} while (time < 15);

	if (connection_status == SOCKET_ERROR)
	{	
		perror("connect()");
		closesocket(network_socket);
		exit(errno);
	}	
	return network_socket;
}
