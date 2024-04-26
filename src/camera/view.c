/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** view
*/

#include <stdlib.h>
#include <time.h>
#include "temp.h"
#include "maps.h"

void init_cam(win_t *window, world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if (world->entity[i].mask & COMP_PLAYER == COMP_PLAYER)
            sfView_setCenter(window->cam.view,
            world->entity[i].comp_position.position);
    sfRenderWindow_setView(window->window, window->cam.view);
}

void init_view(win_t *window)
{
    window->cam.view_rect = (sfFloatRect) {0., 0., 624, 351};
    window->cam.view = sfView_createFromRect(window->cam.view_rect);
    sfRenderWindow_setView(window->window, window->cam.view);
}

void update_cam(win_t *window, entity_t *entity,
    map_list_t *map_list, sfVector2f offset)
{
    sfVector2f cam_pos = sfView_getCenter(window->cam.view);
    sfVector2f player_pos = entity->comp_position.position;
    int cam_width = window->cam.view_rect.width;
    int cam_height = window->cam.view_rect.height;
    sfVector2f map_size = map_list->maps->size;

    if (offset.x <= 0 && cam_pos.x - cam_width / 2 > 0 - offset.x &&
        abs(player_pos.x - cam_pos.x) < THRESHOLD)
        sfView_move(window->cam.view, (sfVector2f) {offset.x, 0});
    if (offset.x >= 0 && cam_pos.x + cam_width / 2 < map_size.x + offset.x &&
        abs(player_pos.x - cam_pos.x) < THRESHOLD)
        sfView_move(window->cam.view, (sfVector2f) {offset.x, 0});
    if (offset.y <= 0 && cam_pos.y - cam_height / 2 > 0 - offset.y &&
        abs(player_pos.y - cam_pos.y) < THRESHOLD)
        sfView_move(window->cam.view, (sfVector2f) {0, offset.y});
    if (offset.y >= 0 && cam_pos.y + cam_height / 2 < map_size.y + offset.y
        && abs(player_pos.y - cam_pos.y) < THRESHOLD)
        sfView_move(window->cam.view, (sfVector2f) {0, offset.y});
}
