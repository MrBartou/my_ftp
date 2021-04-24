##
## EPITECH PROJECT, 2021
## my_ftp
## File description:
## Makefile
##

SRC 		= 	src/main.c \
				src/help.c \
				src/init_serv.c \
				src/client/client.c \

CFLAGS		+=	-W -Wall -I ./include

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