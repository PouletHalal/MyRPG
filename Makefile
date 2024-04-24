##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC	=	src/main.c			\
		src/start.c			\
		src/sys_render.c		\
		src/sys_input_and_event.c	\
		src/sys_position.c		\
		src/sys_player.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_rpg

CFLAGS =	-I include

CPPFLGS = 	-W -Wall -Wextra

DBFLAGS = 	-g -g3 -ggdb

LDFLAGS = 	-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS)

test:
	make re
	./my_rpg 
	make clean > /dev/null

debuger: $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS) $(DBFLAGS)

clean:
	rm -f $(OBJ)

debug: 	fclean
	make debuger

fclean: clean
	rm -f $(NAME)

re:     fclean all

.PHONY:	all clean fclean re

style:	fclean
	coding-style . .
	cat coding-style-reports.log
	rm -f coding-style-reports.log
