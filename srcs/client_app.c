#include "sys_incl.h"
#include "ft.h"

void	app(SOCKET socket)
{
	char pseudo[24];
	int statu;
	fd_set readfs;
	
	getname(pseudo, sizeof(pseudo));

	while (1)
	{
		char *buffer = malloc(sizeof(char) * 1024);
		char *msg = malloc(sizeof(char) * 1000);

		FD_ZERO(&readfs);
		FD_SET(socket, &readfs);
		FD_SET(STDIN_FILENO, &readfs);

		if (select(socket + 1, &readfs, NULL, NULL, NULL) == -1)
			get_error("select()", 1, -1);

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
	closesocket(socket);
}
