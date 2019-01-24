.SILENT:

OPTION= -lpthread

FLAGS= -Wextra -Werror

SRC=	srcs/client_app.c \
	srcs/client_connect.c \
	srcs/main.c \
	srcs/ft_files/ft_display.c \
	srcs/ft_files/ft_general.c \
	srcs/ft_files/ft_messages.c

all:
	gcc $(FLAGS) $(SRC) -o IRC_Client -I includes/ -g

clean:
	rm IRC_Client

re: clean all
