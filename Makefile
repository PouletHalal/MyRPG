##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC	=	src/main.c					\
		src/start.c					\
		src/animation.c				\
		src/sys_render.c			\
		src/sys_input_and_event.c	\
		src/position/sys_position.c		\
		src/position/vectors.c	\
		src/stats/sys_stat.c	\
		src/sys_mob.c	\
		src/camera/view.c	\
		src/camera/camera_movements.c	\
		src/error_handling/parsing_handling.c	\
		src/player/sys_player.c	\
		src/player/player_collisions.c	\
		src/portals/init_portals.c	\
		src/portals/portal_parsing.c	\
		src/portals/portal_parsing2.c	\
		src/map_loading/parsing.c	\
		src/map_loading/init_tilesets.c	\
		src/ecs/components_inits.c	\
		src/npcs/init_npc.c	\
		src/npcs/dialogs_gestion.c	\
		src/npcs/dialogs_rendering.c	\
		src/npcs/npc_gestion.c	\
		src/npcs/no_input_dialogs.c	\
		src/npcs/npc_parsing.c	\
		src/npcs/npc_parsing2.c	\
		src/npcs/npc_parsing3.c	\
		src/rendering/map_rendering.c	\
		src/rendering/window_rendering.c	\
		src/lib/my_str_to_word_array.c	\
		src/lib/my_strcat.c	\
		src/sounds/init_sounds.c	\
		src/sounds/sounds_gestion.c	\
		src/inventory/init_inventory.c	\
		src/inventory/inventory_rendering.c	\
		src/inventory/inventory_gestion.c	\
		src/inventory/init_items.c	\
		src/inventory/items_gestion.c	\
		src/inventory/items_parsing.c	\
		src/inventory/items_parsing2.c	\
		src/inventory/items_rendering.c	\
		src/inventory/items_stats.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	my_rpg

CFLAGS +=	-I include

CPPFLGS += 	-W -Wall -Wextra

DBFLAGS = 	-g -g3 -fsanitize=address

LDFLAGS = 	-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS)

test:
	make re
	./$(NAME)
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
