/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Temp Header File
*/

#ifndef TEMP_H_
    #define TEMP_H_

    #include "world.h"
    #include "window.h"

sfBool is_key_pressed(entity_t *entity, sfKeyCode code);
sfBool is_key_down(entity_t *entity, sfKeyCode code);
void init_textures(world_t *world);
int len_array(char **array);
int find_empty(world_t *world);


void read_portalconf(world_t *world);
void read_npcconf(world_t *world);
void read_mobconf(world_t *world);


sfBool collide_entity(entity_t *entity, entity_t *bis, sfVector2f velocity);
void npc_collision(win_t *window, world_t *world, entity_t *entity);
sfBool check_collision(entity_t *entity, world_t *world,
    sfVector2f velocity, win_t *window);

void sys_input_and_event(world_t *world, win_t *window);
void sys_position(world_t *world, win_t *window);

void add_vector(entity_t *entity, sfVector2f vector, size_t lenght);
sfVector2f get_mouv_vector(entity_t *entity);

void display_inventory(win_t *window, world_t *world);
void item_events(win_t *window, world_t *world, entity_t *entity);
void display_tooltips(win_t *window, entity_t *item, sfVector2f pos);

#endif /* !TEMP_H_ */
