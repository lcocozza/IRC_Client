.SILENT:

NAME= IRC_Client

LIB= -lncurses -lpanel

PACKAGE= libncurses5-dev libncursesw5-dev

OPTION= -I includes/ -g -o

FLAGS= -Wextra -Werror

SRC=	srcs/main.c \
	srcs/ft_files/ft_client.c \
	srcs/ft_files/ft_network.c \
	srcs/ft_files/ft_display.c \
	srcs/ft_files/ft_general.c \
	srcs/ft_files/ft_messages.c \
	srcs/ft_files/ft_input.c \
	srcs/ft_files/ft_output.c 

install:
	sudo apt-get install $(PACKAGE)

gcc:
	gcc $(FLAGS) $(SRC) $(LIB) $(OPTION) $(NAME)

clean:
	rm $(NAME)

re: clean gcc

all: install gcc
