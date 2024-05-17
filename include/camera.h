/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** camera
*/

#ifndef CAMERA_H_
    #define CAMERA_H_

    #include "temp.h"

    #define CAM_THRESHOLD 10

void set_destination(win_t *window, sfVector2f *destination);
void init_view(win_t *window);
void init_cam(win_t *window, world_t *world, entity_t *entity);
void update_cam(win_t *window, entity_t *entity,
    map_list_t *map_list, sfVector2f offset);
void resize_cam(win_t *window, map_list_t *map);
void move_cam(win_t *window, map_list_t *map);
bool is_in_cam_range(win_t *window, entity_t *entity);
void move_to_destination(win_t *window);
#endif /* !CAMERA_H_ */
