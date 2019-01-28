#ifndef FT_H
#define FT_H

/* ft_general.c */

void	get_error(char *str, int quit, SOCKET socket);
void	getname(char *name, size_t namesize);
void	arg(int argc, char **argv);

/* ft_messages.c */

void	send_message(SOCKET socket, char *buffer);
int	receive_message(SOCKET socket, char *buffer);
void	cleanMsg(char *buffer, char *msg);

/* ft_display.c */

void	title(void);


/* ft_network.c */

int	init_connection(char **argv);
static void	init(void);
static void	end(void);


/* ft_client.c */

void	app(SOCKET socket);


#endif
