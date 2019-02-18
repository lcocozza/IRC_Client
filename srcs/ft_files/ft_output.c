#include "sys_incl.h"
#include "struct.h"
#include "ft.h"

void	print_output(t_win *screen, t_data *data)
{
	FILE *output_log = NULL;
	char pseudo[PSDSIZE] = {0};
	char msg[MSGSIZE] = {0};
	int result_y;
	int pair;
	int i;

	output_log = fopen("output.log", "r");

	if (output_log == NULL)
		end_prog();

	for (i = 0; i < data->line; i++)
		fgets(msg, MSGSIZE, output_log);
	
	werase(screen[1].win_t);
	while (fscanf(output_log, "$%s ", pseudo) != EOF)
	{
		if (strcmp(pseudo, "[serveur]") == 0)
			pair = 2;
		else
			pair = 1;

		fgets(msg, MSGSIZE, output_log);

		wattron(screen[1].win_t, A_BOLD | COLOR_PAIR(pair));
		mvwprintw(screen[1].win_t, data->cursor_y, 0, pseudo);
		wattroff(screen[1].win_t, A_BOLD | COLOR_PAIR(pair));
		data->cursor_x = strlen(pseudo);

		mvwprintw(screen[1].win_t, data->cursor_y, data->cursor_x + 1, msg);
		result_y = (strlen(msg) + strlen(pseudo)) / screen[1].max_x;
		data->cursor_y = data->cursor_y + ((result_y < 1) ? 1 : result_y + 1);
		data->cursor_x = 0;
	}
	data->cursor_y = 0;
	fclose(output_log);
}

void	insert_output(t_win *screen, t_data *data, char *buffer)
{
	FILE *output_log = NULL;
	char msg[MSGSIZE] = {0};
	int i;

	output_log = fopen("output.log", "a+");

	if (output_log == NULL)
		end_prog();

	fputs(buffer, output_log);
	fputs("\n", output_log);
	rewind(output_log);
	
	for (i = 0; fgets(msg, MSGSIZE, output_log) != NULL; i++) ;

	if (i > screen[1].max_y)
		scroll_text(screen, data, 1);
	else
		print_output(screen, data);

	fclose(output_log);
}

void	scroll_text(t_win *screen, t_data *data, int dir)
{
	FILE *output_log = NULL;
	char msg[MSGSIZE] = {0};
	int maxline;

	output_log = fopen("output.log", "r");
	for (maxline = 0; fgets(msg, MSGSIZE, output_log) != NULL; maxline++) ;
	fclose(output_log);

	if (dir == 1 && data->line < maxline - 1)
		data->line++;
	else if (dir == -1 && data->line > 0)
		data->line--;

	print_output(screen, data);
}
