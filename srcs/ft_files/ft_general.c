#include "sys_incl.h"
#include "ft.h"

void	get_error(char *str, int quit, SOCKET socket)
{
	if (str != NULL)
		perror(str);
	if (socket != -1)
		closesocket(socket);
	if (quit == 1)
		exit(errno);
}

void	getname(char *name, size_t namesize)
{
	char *tmp = NULL;

	tmp = malloc(namesize);
	strcpy(name, "[");
	getlogin_r(tmp, namesize);
	strcat(name, tmp);
	strcat(name, "] ");
	free(tmp);
}

void	arg(int argc, char **argv)
{
	if (argc != 3)
	{
		printf(	"Invalide Argument.\n"
			"Usage: ./%s [ip] [port]\n", argv[0]);
		exit(0);
	}

}
