#include "sys_incl.h"
#include "struct.h"
#include "ft.h"

void	init_screen(t_win *screen, char *title)
{
	int i;

	initscr();

	if (has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	use_default_colors();
	start_color();
	init_pair(1, COLOR_YELLOW, -1);
	init_pair(2, COLOR_RED, -1);

	screen[0].win_b = newwin(5, COLS - 40, LINES - 5, 20);	// input
	screen[1].win_b = newwin(LINES - 8, COLS - 40, 3, 20);	//output
	screen[2].win_b = newwin(LINES - 3, 20, 3, 0);		// chan
	screen[3].win_b = newwin(3, COLS, 0, 0);		// title
	screen[4].win_b = newwin(LINES - 3, 20, 3, COLS - 20);	// users

	for (i = 0; i <= 4; i++)
	{
		box(screen[i].win_b, ACS_VLINE, ACS_HLINE);

		getmaxyx(screen[i].win_b, screen[i].max_y, screen[i].max_x);
		getbegyx(screen[i].win_b, screen[i].beg_y, screen[i].beg_x);

		screen[i].win_t = newwin(screen[i].max_y - 2, screen[i].max_x - 2, screen[i].beg_y + 1, screen[i].beg_x + 1);

		getmaxyx(screen[i].win_t, screen[i].max_y, screen[i].max_x);
		getbegyx(screen[i].win_t, screen[i].beg_y, screen[i].beg_x);

		screen[i].pan_b = new_panel(screen[i].win_b);
		screen[i].pan_t = new_panel(screen[i].win_t);
		top_panel(screen[i].pan_t);
	}

	keypad(screen[0].win_t, TRUE);

	wattron(screen[3].win_t, A_BOLD | COLOR_PAIR(1));
	mvwprintw(screen[3].win_t, 0, (COLS / 2) - (strlen(title) / 2), title);
	wattroff(screen[3].win_t, A_BOLD | COLOR_PAIR(1));

	wmove(screen[0].win_t, 0, 0);
	noecho();

	update_panels();
	doupdate();
	wrefresh(screen[0].win_t);
}
