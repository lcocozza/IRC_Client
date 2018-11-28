#include "IRC_Client.h"

int	main(int argc, char **argv)
{
	int sock;

	arg(argc, argv);
	init_connection(argv);

	return 0;
}
