/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** player
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "world.h"
    #include "window.h"

void sys_player(win_t *window, world_t *world);
void update_cam(win_t *window, entity_t *entity,
    map_list_t *map_list, sfVector2f offset);
void update_sprite_animation(entity_t *entity,
    int anim_id, int count, int framerate);
bool is_colliding(world_t *world, entity_t *entity, sfVector2f offset);
int find_comp(world_t *world, int comp);
void player_movements(win_t *window, entity_t *entity, world_t *world);

#endif /* !PLAYER_H_ */
