#ifndef STRUCT_H
#define STRUCT_H

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

typedef struct s_win 
{
	WINDOW *win_b;
	WINDOW *win_t;
	PANEL *pan_b;
	PANEL *pan_t;
	int max_y;
	int max_x;
	int beg_y;
	int beg_x;

} t_win;

typedef	struct s_data
{
	int cursor_y;
	int cursor_x;
	int line;

} t_data;

#endif
