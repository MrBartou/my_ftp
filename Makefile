##
## EPITECH PROJECT, 2021
## my_ftp
## File description:
## Makefile
##

NM_SRC 		= 	src/main.c \

CFLAGS		+=	-W -Wall -I ./include

OBJ_NM		=	$(NM_SRC:.c=.o)

NM_NAME		=	my_ftp

all:		$(NM_NAME)

nm:			$(NM_NAME)

$(NM_NAME): $(OBJ_NM)
			gcc $(OBJ_NM) -o $(NM_NAME)

clean:
			rm -f $(OBJ_NM)

fclean:		clean
			rm -f $(NM_NAME)

re:			fclean all

.PHONY: 	all clean fclean re