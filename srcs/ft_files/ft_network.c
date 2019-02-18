#include "sys_incl.h"
#include "struct.h"
#include "ft.h"

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
		printf("try to connect...\n");
		connection_status = connect(network_socket, (SOCKADDR *) &server_address, sizeof(SOCKADDR));
		if (connection_status == SOCKET_ERROR)
			sleep(1);
		else
			break;
		time++;
	} while (time < 15);

	if (connection_status == SOCKET_ERROR)
		get_error("connect()", 1, network_socket);
	
	return network_socket;
}

void	send_message(SOCKET socket, char *buffer)
{
	//int i;

	//for (i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++) ;
	//buffer[i] = '\0';

	if (send(socket, buffer, strlen(buffer), 0) < 0)
		get_error("send()", 1, -1);
}

int	receive_message(SOCKET socket, char *buffer)
{
	int statu = 0;
	if ((statu = recv(socket, buffer, BUFFSIZE, 0)) < 0)
		get_error("recv()", -1, -1);
	return statu;
}
