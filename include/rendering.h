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


void render_window(win_t *window, world_t *world);
void draw_hitbox(win_t *window, entity_t *entity);
void display_map(win_t *window, map_list_t *map_list, int priority);
void refresh_world(world_t *world, sfClock *clock,
    win_t *window);
void play_animation(entity_t *entity, int animation_index, sfBool does_loop);
void set_sprite(entity_t *entity, animation_t *anim,
    float mult_scale, sfIntRect *rect);
void update_sprite_direction(entity_t *entity);
bool is_in_animation(entity_t *entity);

#endif /* !RENDERING_H_ */
