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
		src/camera/view.c	\
		src/player/sys_player.c	\
		src/player/player_movements.c	\
		src/player/player_collisions.c	\
		src/map_loading/parsing.c	\
		src/map_loading/init_tilesets.c	\
		src/lib/my_str_to_word_array.c	\
		src/lib/my_strcat.c

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
	clear
	cat coding-style-reports.log
	rm -f coding-style-reports.log
