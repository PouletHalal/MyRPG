/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** rendering
*/

#ifndef RENDERING_H_
    #define RENDERING_H_


    #include "temp.h"
    #include "maps.h"


void render_window(win_t *window, world_t *world, map_list_t *map_list);
void draw_hitbox(win_t *window, entity_t *entity);
void display_map(win_t *window, map_list_t *map_list, int priority);
void refresh_world(world_t *world, sfClock *clock,
    win_t *window, map_list_t *map_list);

#endif /* !RENDERING_H_ */
