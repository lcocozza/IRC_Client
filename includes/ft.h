#ifndef FT_H
#define FT_H

/* ft_general.c */

void	get_error(char *str, int quit, SOCKET socket);
void	getname(char *pseudo);
void	arg(int argc, char **argv);
void	cleanMsg(char *buffer, char *msg);
void	end_prog(void);

/* ft_messages.c */

void	send_message(SOCKET socket, char *buffer);
int	receive_message(SOCKET socket, char *buffer);
void	cleanMsg(char *buffer, char *msg);

/* ft_display.c */

void	init_screen(t_win *screen, char *title);

/* ft_network.c */

int	init_connection(char **argv);
void	send_message(SOCKET socket, char *buffer);
int	receive_message(SOCKET socket, char *buffer);

/* ft_client.c */

void	app(SOCKET socket, t_win *screen);

/* ft_input.c */

void	get_input_msg(t_win *screen, t_data *data, char *pseudo, int socket);
void	get_input(t_win *screen, t_data *data, char *pseudo, int socket);
void	move_cursor(t_win *screen, int dir, int y, int x);
void	backspace(t_win *screen);
void	insert_input(t_win *screen, int key);
void	print_input(t_win *screen);

/* ft_output.c */

void	scroll_text(t_win *screen, t_data *data, int dir);
void	print_output(t_win *screen, t_data *data);
void	insert_output(t_win *screen, t_data *data, char *buffer);

#endif
