#include "sys_incl.h"
#include "struct.h"
#include "ft.h"

void	get_error(char *str, int quit, SOCKET socket)
{
	if (str != NULL)
		perror(str);
	if (socket != -1)
		close(socket);
	if (quit == 1)
		end_prog();
}

void	getname(char *pseudo)
{
	char tmp[PSDSIZE];

	getlogin_r(tmp, sizeof(char) * PSDSIZE);

	strcpy(pseudo, "[");
	strcat(pseudo, tmp);
	strcat(pseudo, "] ");
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

void	cleanMsg(char *buffer, char *msg)
{
	memset(buffer, 0, BUFFSIZE);
	memset(msg, 0, MSGSIZE);
}

void	end_prog(void)
{
	endwin();
	remove("output.log");
	remove("input.log");
	exit(0);
}
