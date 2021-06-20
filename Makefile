##
## EPITECH PROJECT, 2021
## my_ftp
## File description:
## Makefile
##

SRC 		= 	src/main.c \
				src/help.c \
				src/server/init_serv.c \
				src/server/loop.c \
				src/cmd/cwd.c \
				src/cmd/help.c \
				src/cmd/pass.c \
				src/cmd/pwd.c \
				src/cmd/quit.c \
				src/cmd/user.c \
				src/cmd/cdup.c \
				src/client/client.c \
				src/client/check_command.c \
				src/lib/my_str_to_word_array.c \
				src/lib/getline.c \

CFLAGS		+= -I ./include

OBJ		=	$(SRC:.c=.o)

NAME		=	my_ftp

all:		$(NAME)

nm:			$(NAME)

$(NAME): $(OBJ)
			gcc $(OBJ) -o $(NAME)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY: 	all clean fclean re