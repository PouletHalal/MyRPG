/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** player
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "temp.h"
    #include "maps.h"

void sys_player(win_t *window, world_t *world, map_list_t *map_list);
void update_cam(win_t *window, entity_t *entity,
    map_list_t *map_list, sfVector2f offset);
void player_events(win_t *window, entity_t *entity, world_t *world,
    map_list_t *map_list);
void update_sprite_animation(entity_t *entity,
    int anim_id, int count, int framerate);
sfBool is_colliding(entity_t *entity,
    map_list_t *map_list, sfVector2f offset);
int find_player(world_t *world);
void player_movements(win_t *window, entity_t *entity, world_t *world,
    map_list_t *map_list);

#endif /* !PLAYER_H_ */
