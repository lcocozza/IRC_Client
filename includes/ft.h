void	app(SOCKET socket);
static void	init(void);
static void	end(void);
void	arg(int argc, char **argv);
int	init_connection(char **argv);

/* ft_general.c */

void	get_error(char *str, int quit, SOCKET socket);
void	getname(char *name, size_t namesize);

/* ft_messages.c */

void	send_message(SOCKET socket, char *buffer);
int	receive_message(SOCKET socket, char *buffer);
void	cleanMsg(char *buffer, char *msg);

/* ft_display.c */

void	title(void);
