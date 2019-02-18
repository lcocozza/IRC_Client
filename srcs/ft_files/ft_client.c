#include "sys_incl.h"
#include "struct.h"
#include "ft.h"

void	app(SOCKET socket, t_win *screen)
{
	char buffer[BUFFSIZE] = {0};
	char pseudo[PSDSIZE] = {0};
	char msg[MSGSIZE] = {0};
	FILE *file = NULL;
	int statu;
	fd_set readfs;
	t_data data;

	data.cursor_y = 0;
	data.cursor_x = 0;
	data.line = 0;
	
	getname(pseudo);

	file = fopen("input.log", "w");
	fclose(file);
	file = fopen("output.log", "w");
	fclose(file);

	while (1)
	{
		FD_ZERO(&readfs);
		FD_SET(socket, &readfs);
		FD_SET(STDIN_FILENO, &readfs);

		if (select(socket + 1, &readfs, NULL, NULL, NULL) == -1)
			get_error("select()", 1, -1);

		if (FD_ISSET(STDIN_FILENO, &readfs))
		{
			get_input(screen, &data, pseudo, socket);
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
				insert_output(screen, &data, buffer);
				cleanMsg(buffer, msg);
			}
		}
		wrefresh(screen[1].win_t);
		wrefresh(screen[0].win_t);
	}
	close(socket);
}
