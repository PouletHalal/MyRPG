##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC	=	src/animation.c				\
		src/animation/animations_parsing.c	\
		src/animation/animations_parsing2.c	\
		src/animation/init_animations.c	\
		src/camera/camera_movements.c	\
		src/light/light.c				\
		src/spell/effect.c		\
		src/spell/sys_spell.c	\
		src/spell/init_spell.c	\
		src/spell/spells_parsing.c	\
		src/spell/effect_parsing.c	\
		src/spell/init_effects.c	\
		src/camera/view.c	\
		src/error_handling/parsing_handling.c	\
		src/free/kill.c	\
		src/hud/hud_gestion.c	\
		src/hud/init_hud.c	\
		src/inventory/init_inventory.c	\
		src/inventory/inventory_gestion.c	\
		src/inventory/inventory_rendering.c	\
		src/inventory/init_items.c	\
		src/inventory/items_gestion.c	\
		src/inventory/items_parsing.c	\
		src/inventory/items_parsing2.c	\
		src/inventory/items_rendering.c	\
		src/inventory/items_stats.c	\
		src/inventory/slots.c	\
		src/mouse.c 	\
		src/lib/my_str_to_word_array.c	\
		src/lib/my_strcat.c	\
		src/main.c	\
		src/map_loading/init_tilesets.c	\
		src/map_loading/parsing.c	\
		src/memory.c	\
		src/mob/init_mob.c	\
		src/mob/mob_death.c	\
		src/mob/mob_parsing.c	\
		src/mob/mob_parsing2.c	\
		src/mob/mob_parsing3.c	\
		src/mob/mob_parsing4.c	\
		src/mob/spawn_mob.c	\
		src/mob/sys_mob.c	\
		src/npcs/dialogs_gestion.c	\
		src/npcs/dialogs_rendering.c	\
		src/npcs/init_npc.c	\
		src/npcs/npc_gestion.c	\
		src/npcs/no_input_dialogs.c	\
		src/npcs/npc_parsing.c	\
		src/npcs/npc_parsing2.c	\
		src/npcs/npc_parsing3.c	\
		src/npcs/npc_parsing4.c	\
		src/npcs/sys_npc.c	\
		src/particle/disp_part.c	\
		src/particle/init_particle.c	\
		src/particle/part_parsing.c	\
		src/particle/part_parsing1.c	\
		src/particle/part_parsing2.c	\
		src/particle/particle.c	\
		src/player/player_collisions.c	\
		src/player/sys_player.c	\
		src/portals/init_portals.c	\
		src/portals/portal_parsing.c	\
		src/portals/portal_parsing2.c	\
		src/read_config.c	\
		src/rendering/map_rendering.c	\
		src/rendering/window_rendering.c	\
		src/sounds/init_sounds.c	\
		src/sounds/sounds_gestion.c	\
		src/stats/sys_stat.c	\
		src/sys_input_and_event.c	\
		src/sys_render.c			\
		src/ecs/components_inits.c	\
		src/position/sys_position.c		\
		src/position/vectors.c	\
		src/start.c	\
		src/ui/init_ui.c	\
		src/ui/ui_parsing.c	\
		src/ui/ui_parsing2.c	\
		src/ui/sys_ui.c	\
		src/map_loading/map_drawing.c	\
		src/spell/spell_parsing2.c	\
		src/inventory/item_stats2.c	\
		src/ui/button_functs.c	\

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
