#include "IRC_Client.h"

int	main(int argc, char **argv)
{
	int sock;

	arg(argc, argv);
	
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
	{
		perror("socket()");
		exit(errno);
	}

	return 0;
}
