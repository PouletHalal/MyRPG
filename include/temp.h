/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Temp Header File
*/

#ifndef TEMP_H_
    #define TEMP_H_

    #include <SFML/Graphics.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include "maps.h"
    #include "ecs.h"

typedef struct cam_s {
    sfFloatRect view_rect;
    sfView *view;
} cam_t;

typedef struct window_s {
    sfVideoMode mode;
    sfRenderWindow *window;
    sfEvent event;
    sfVector2f windows_scale;
    cam_t cam;
} win_t;

sfBool is_key_pressed(entity_t *entity, sfKeyCode code);
sfBool is_key_down(entity_t *entity, sfKeyCode code);
void init_textures(world_t *world);
int len_array(char **array);
int find_empty(world_t *world);


void read_portalconf(world_t *world);
void read_npcconf(world_t *world);

sfBool collide_entity(entity_t *entity, entity_t *bis, sfVector2f velocity);
bool npc_collision(win_t *window, world_t *world, entity_t *entity);

void sys_input_and_event(world_t *world, win_t *window);
void sys_position(world_t *world, win_t *window);

void add_vector(entity_t *entity, sfVector2f vector, size_t lenght);

#endif /* !TEMP_H_ */
