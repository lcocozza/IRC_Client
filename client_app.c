#include "header.h"

void	app(SOCKET socket)
{
	char buffer[1024];
	int statu;
	fd_set readfs;

	while(1)
	{
		FD_ZERO(&readfs);
		FD_SET(socket, &readfs);
		FD_SET(STDIN_FILENO, &readfs);

		if (select(socket + 1, &readfs, NULL, NULL, NULL) == -1)
		{
			perror("select()");
			exit(errno);
		}
		if (FD_ISSET(STDIN_FILENO, &readfs))
		{
			fgets(buffer, sizeof(char) * 1024, stdin);
			send_message(socket, buffer);
		}
		else if (FD_ISSET(socket, &readfs))
		{
			statu = receive_message(socket, buffer);
			if (statu < 0)
			{
				printf("Server disconnected !\n");
				break;
			}
			else
			{
				printf("%s\n", buffer);
				cleanBuffer(buffer);
			}
		}
	}
	close_connection(socket);
}

void	send_message(SOCKET socket, char *buffer)
{	
	int i;

	for (i = 0; buffer[i] != '\n'; i++) ;
	buffer[i] = '\0';

	if (send(socket, buffer, strlen(buffer), 0) < 0)
	{
		perror("send()");
		exit(errno);
	}
	cleanBuffer(buffer);
}

int	receive_message(SOCKET socket, char *buffer)
{
	int statu = 0;
	if ((statu = recv(socket, buffer, 1024, 0)) < 0)
		perror("recv()");
	return statu;
}

void cleanBuffer(char *buffer)
{
	int i;
	for (i = 1; buffer[i] != '\0'; i++)
		buffer[i - 1] = '\0';
	buffer[i] = '\0';
}
