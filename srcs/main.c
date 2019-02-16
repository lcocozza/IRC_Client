#include "sys_incl.h"
#include "struct.h"
#include "ft.h"

int	main(int argc, char **argv)
{
	int socket;
	char title[] = "IRC v0.5";
	t_win screen[5];

	arg(argc, argv);
	socket = init_connection(argv);
	init_screen(screen, title);
	app(socket, screen);
	end_prog();

	return 0;
}
