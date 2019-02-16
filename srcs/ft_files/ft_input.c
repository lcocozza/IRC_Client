#include "sys_incl.h"
#include "struct.h"
#include "ft.h"

void	move_cursor(t_win *screen, int dir, int y, int x)
{
	FILE *input_log = NULL;
	char msg[MSGSIZE] = {0};
	int max;

	input_log = fopen("input.log", "r");
	
	if (y == -1)
		y = getcury(screen[0].win_t);
	if (x == -1)
		x = getcurx(screen[0].win_t);

	fgets(msg , MSGSIZE, input_log);
	max = strlen(msg);

	fclose(input_log);

	if (dir == -1)
		wmove(screen[0].win_t, y, x - 1);
	else if (dir == 1 && x < max)
		wmove(screen[0].win_t, y, x + 1);
	
	wrefresh(screen[0].win_t);
}

void	get_input_msg(t_win *screen, t_data *data, char *pseudo, int socket)
{
	char buffer[BUFFSIZE] = {0};
	char msg[MSGSIZE] = {0};
	FILE *input_log = NULL;

	input_log = fopen("input.log", "r");

	fgets(msg, MSGSIZE, input_log);
	fclose(input_log);
	remove("input.log");
	input_log = fopen("input.log", "w");
	fclose(input_log);

	if (strcmp(msg, "/quite") == 0)
		end_prog();
	if (strcmp(msg, "") != 0)
	{
		strcpy(buffer, "$");
		strcat(buffer, pseudo);
		strcat(buffer, msg);
		insert_output(buffer);
		werase(screen[1].win_t);
		print_output(screen, data);
		send_message(socket, buffer);
	}
	werase(screen[0].win_t);
}

void	print_input(t_win *screen)
{
	FILE *input_log = NULL;
	char msg[MSGSIZE] = {0};

	input_log = fopen("input.log", "r");

	werase(screen[0].win_t);
	fgets(msg, MSGSIZE, input_log);
	wprintw(screen[0].win_t, msg);
	wrefresh(screen[0].win_t);

	fclose(input_log);
}

void	insert_input(t_win *screen, int key)
{
	FILE *input_log = NULL;
	char msg[MSGSIZE] = {0};
	int y, x;
	int i;
	int j;

	getyx(screen[0].win_t, y, x);
	i = x + (screen[0].max_x * y);

	input_log = fopen("input.log", "r");
	fgets(msg, MSGSIZE, input_log);
	j = strlen(msg) + 1;

	for ( ; j >= i; j--)
		msg[j + 1] = msg[j];
	msg[i] = key;

	fclose(input_log);

	input_log = fopen("input.log", "w+");
	fputs(msg, input_log);

	fclose(input_log);
	print_input(screen);

	move_cursor(screen, 1, y, x);
}

void	backspace(t_win *screen)
{
	FILE *input_log = NULL;
	char msg[MSGSIZE] = {0};
	int y, x = getyx(screen[0].win_t, y, x);
	int i = (x - 1) + (screen[0].max_x * y);

	input_log = fopen("input.log", "r");
	fgets(msg, MSGSIZE, input_log);

	for ( ; msg[i] != '\0'; ++i)
		msg[i] = msg[i + 1];

	fclose(input_log);

	input_log = fopen("input.log", "w+");
	fputs(msg, input_log);

	fclose(input_log);
	print_input(screen);

	move_cursor(screen, -1, y, x);
}

void	get_input(t_win *screen, t_data *data, char *pseudo, int socket)
{
	int key;

	key = wgetch(screen[0].win_t);

	if (key == KEY_LEFT)
		move_cursor(screen, -1, -1, -1);
	else if (key == KEY_RIGHT)
		move_cursor(screen, 1, -1, -1);
	else if (key == KEY_UP)
		scroll_text(screen, data, 1);
	else if (key == KEY_DOWN)
		scroll_text(screen, data, -1);
	else if (key >= ' ' && key <= '~')
		insert_input(screen, key);
	else if (key == KEY_BACKSPACE)
		backspace(screen);
	else if (key == '\n')
		get_input_msg(screen, data, pseudo, socket);
}
