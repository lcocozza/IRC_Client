#include "header.h"

void	app(SOCKET socket)
{
	char pseudo[24];
	int statu;
	fd_set readfs;
	
	strcpy(pseudo, "[");
	strcat(pseudo, getname(sizeof(pseudo)));
	strcat(pseudo, "] ");

	while (1)
	{
		char *buffer = malloc(sizeof(char) * 1024);
		char *msg = malloc(sizeof(char) * 1000);

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
			fgets(msg, sizeof(char) * 1000, stdin);
			strcpy(buffer, pseudo);
			strcat(buffer, msg);
			send_message(socket, buffer);
			cleanMsg(buffer, msg);
		}
		else if (FD_ISSET(socket, &readfs))
		{
			statu = receive_message(socket, buffer);
			if (statu == 0)
			{
				printf("Server disconnected !\n");
				break;
			}
			else
			{
				printf("%s\n", buffer);
				cleanMsg(buffer, msg);
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
}

int	receive_message(SOCKET socket, char *buffer)
{
	int statu = 0;
	if ((statu = recv(socket, buffer, 1024, 0)) < 0)
		perror("recv()");
	return statu;
}

void	cleanMsg(char *buffer, char *msg)
{
	memset(buffer, 0, strlen(buffer));
	memset(msg, 0, strlen(msg));
	free(buffer);
	free(msg);
}

char	*getname(size_t namesize)
{
	char *tmp = NULL;

	tmp = malloc(namesize);
	getlogin_r(tmp, namesize);

	return tmp;
}
