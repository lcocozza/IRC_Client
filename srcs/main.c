#include "sys_incl.h"
#include "ft.h"

int	main(int argc, char **argv)
{
	int socket;

	arg(argc, argv);
	title();
	socket = init_connection(argv);
	app(socket);
	closesocket(socket);

	return 0;
}
