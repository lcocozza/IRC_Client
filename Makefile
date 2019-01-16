.SILENT:

OPTION= -lpthread

FLAGS= -Wall -Wextra -Werror

SRC=	srcs/client_app.c \
	srcs/client_connect.c \
	srcs/main.c \
	srcs/display.c

all:
	gcc $(FLAGS) $(SRC) -o IRC_Client -I includes/

clean:
	rm IRC_Client

re: clean all
