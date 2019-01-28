.SILENT:

OPTION= -lpthread

FLAGS= -Wextra -Werror

SRC=	srcs/main.c \
	srcs/ft_files/ft_client.c \
	srcs/ft_files/ft_network.c \
	srcs/ft_files/ft_display.c \
	srcs/ft_files/ft_general.c \
	srcs/ft_files/ft_messages.c

all:
	gcc $(FLAGS) $(SRC) -o IRC_Client -I includes/ -g

clean:
	rm IRC_Client

re: clean all
