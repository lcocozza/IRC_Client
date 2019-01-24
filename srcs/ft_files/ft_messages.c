#include "sys_incl.h"
#include "ft.h"

void	send_message(SOCKET socket, char *buffer)
{	
	int i;

	for (i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++) ;
	buffer[i] = '\0';

	if (send(socket, buffer, strlen(buffer), 0) < 0)
		get_error("send()", 1, -1);
}

int	receive_message(SOCKET socket, char *buffer)
{
	int statu = 0;
	if ((statu = recv(socket, buffer, 1024, 0)) < 0)
		get_error("recv()", -1, -1);
	return statu;
}

void	cleanMsg(char *buffer, char *msg)
{
	memset(buffer, 0, strlen(buffer));
	memset(msg, 0, strlen(msg));
	free(buffer);
	free(msg);
}
