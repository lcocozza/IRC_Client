#include "header.h"

int	main(int argc, char **argv)
{
	int socket;

	arg(argc, argv);
	title();
	socket = init_connection(argv);
	app(socket);
	close_connection(socket);

	return 0;
}
