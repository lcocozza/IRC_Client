#include "header.h"

int	main(int argc, char **argv)
{
	int socket;

	arg(argc, argv);
	socket = init_connection(argv);
	app(socket);
	closeconnection(socket);

	return 0;
}
