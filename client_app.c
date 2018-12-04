#include "header.h"

int	app(int socket)
{
	char server_response[1024];

	recv(socket,&server_response, sizeof(server_response), 0);
	printf("Server: %s\n", server_response);
}
