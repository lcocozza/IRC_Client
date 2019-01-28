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

int	init_connection(char **argv)
{
	SOCKET network_socket;
	int connection_status;
	int time = 0;

	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN server_address = {0};
	struct hostent *hostinfo = NULL;

	if (network_socket == INVALID_SOCKET)
		get_error("socket()", 1, network_socket);

	hostinfo = gethostbyname(argv[1]);
	if (hostinfo == NULL)
	{
		printf("Unknow host %s.\n", argv[1]);
		get_error(NULL, 1, network_socket);
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
			break;
		time++;
	} while (time < 15);

	if (connection_status == SOCKET_ERROR)
		get_error("connect()", 1, network_socket);
	
	return network_socket;
}
