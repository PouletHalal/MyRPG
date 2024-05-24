/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** camera_movements
*/

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "temp.h"
#include "maps.h"
#include "camera.h"


static int is_right_size(sfVector2f cam_center, sfVector2f cam_size,
    sfVector2f map_size)
{
    if (cam_center.x - cam_size.x / 2 >= 0
        && cam_center.x + cam_size.x / 2 <= map_size.x
        && cam_center.y - cam_size.y / 2 >= 0
        && cam_center.y + cam_size.y / 2 <= map_size.y)
        return 1;
    return 0;
}

static int move_and_update(sfView *view, sfVector2f offset,
    sfVector2f *cam_center)
{
    sfView_move(view, offset);
    *cam_center = sfView_getCenter(view);
}

void set_destination(win_t *window, sfVector2f *destination)
{
    window->cam.destination = destination;
    window->cam.is_moving = true;
}

void move_to_destination(win_t *window)
{
    sfVector2f cam_center = sfView_getCenter(window->cam.view);
    sfVector2f offset = {0, 0};
    sfVector2f dest = *window->cam.destination;
    double hyp = sqrt((dest.x - cam_center.x) * (dest.x - cam_center.x) +
    ((dest.y - cam_center.y) * (dest.y - cam_center.y)));
    double cos = (dest.x - cam_center.x) / hyp;
    double sin = (dest.y - cam_center.y) / hyp;

    if (window->cam.is_moving == false ||
    (abs(dest.x - cam_center.x)) <= 10 && (abs(dest.y - cam_center.y)) <= 10){
        window->cam.is_moving = false;
        return;
    }
    offset.x = cos * window->cam.offset.x;
    offset.y = sin * window->cam.offset.y;
    if (offset.x == 0. && offset.y == 0.) {
        window->cam.offset = (sfVector2f) {0.5, 0.5};
        window->cam.is_moving = false;
    }
    sfView_move(window->cam.view, offset);
}

void move_cam(win_t *window, map_list_t *map)
{
    sfVector2f cam_size = sfView_getSize(window->cam.view);
    sfVector2f cam_center = sfView_getCenter(window->cam.view);
    sfVector2f map_size = map->maps->size;

    if (is_right_size(cam_center, cam_size, map_size))
        return;
    move_to_destination(window);
    while (cam_center.x - cam_size.x / 2 < 0)
        move_and_update(window->cam.view, (sfVector2f) {1, 0}, &cam_center);
    while (cam_center.x + cam_size.x / 2 > map_size.x)
        move_and_update(window->cam.view, (sfVector2f) {-1, 0}, &cam_center);
    while (cam_center.y - cam_size.y / 2 < 0)
        move_and_update(window->cam.view, (sfVector2f) {0, 1}, &cam_center);
    while (cam_center.y - cam_size.y / 2 > map_size.y)
        move_and_update(window->cam.view, (sfVector2f) {0, -1}, &cam_center);
    if (is_right_size(cam_center, cam_size, map_size))
        return;
}
