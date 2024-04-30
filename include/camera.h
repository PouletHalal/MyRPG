/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** camera
*/

#ifndef CAMERA_H_
    #define CAMERA_H_

    #include "temp.h"


void init_view(win_t *window);
void init_cam(win_t *window, world_t *world);
void update_cam(win_t *window, entity_t *entity,
    map_list_t *map_list, sfVector2f offset);
void resize_cam(win_t *window, map_list_t *map);
void move_cam(win_t *window, map_list_t *map);

#endif /* !CAMERA_H_ */
