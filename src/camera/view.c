/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** view
*/

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "temp.h"
#include "maps.h"
#include "camera.h"

void init_cam(win_t *window, world_t *world, entity_t *entity)
{
    sfView_setCenter(window->cam.view,
    entity->comp_position.position);
    sfRenderWindow_setView(window->window, window->cam.view);
    window->cam.is_moving = false;
}

void init_view(win_t *window)
{
    sfVector2f dest = {0, 0};

    window->cam.view_rect = (sfFloatRect) {0., 0., 624, 351};
    window->cam.view = sfView_createFromRect(window->cam.view_rect);
    window->cam.is_moving = false;
    window->cam.offset = (sfVector2f) {6, 6};
    window->cam.destination = &dest;
}

static bool is_resizable(win_t *window, world_t *world, sfVector2f diff)
{
    if (world->map_list[world->map_id]->has_cam == true) {
        sfView_setSize(window->cam.view,
        world->map_list[world->map_id]->cam_size);
        return true;
    }
    if (diff.x > 0 && diff.y > 0) {
        world->map_list[world->map_id]->has_cam = true;
        world->map_list[world->map_id]->cam_size = sfView_getSize(window->cam.view);
        return true;
    }
    return false;
}

void resize_cam(win_t *window, map_list_t *map, world_t *world)
{
    sfVector2f cam_size = sfView_getSize(window->cam.view);
    sfVector2f map_size = map->maps->size;
    sfVector2f diff = {map_size.x - cam_size.x, map_size.y - cam_size.y};

    if (is_resizable(window, world, diff))
        return;
    while (diff.x < 0 || diff.y < 0) {
        sfView_zoom(window->cam.view, 0.99);
        cam_size = sfView_getSize(window->cam.view);
        diff = (sfVector2f) {map_size.x - cam_size.x, map_size.y - cam_size.y};
    }
    window->cam.view_rect.width = cam_size.x;
    window->cam.view_rect.height = cam_size.y;
    world->map_list[world->map_id]->has_cam = true;
    world->map_list[world->map_id]->cam_size = sfView_getSize(window->cam.view);
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
        abs(player_pos.x - cam_pos.x) < CAM_THRESHOLD)
        sfView_move(window->cam.view, (sfVector2f) {offset.x, 0});
    if (offset.x >= 0 && cam_pos.x + cam_width / 2 < map_size.x + offset.x &&
        abs(player_pos.x - cam_pos.x) < CAM_THRESHOLD)
        sfView_move(window->cam.view, (sfVector2f) {offset.x, 0});
    if (offset.y <= 0 && cam_pos.y - cam_height / 2 > 0 - offset.y &&
        abs(player_pos.y - cam_pos.y) < CAM_THRESHOLD)
        sfView_move(window->cam.view, (sfVector2f) {0, offset.y});
    if (offset.y >= 0 && cam_pos.y + cam_height / 2 < map_size.y + offset.y
        && abs(player_pos.y - cam_pos.y) < CAM_THRESHOLD)
        sfView_move(window->cam.view, (sfVector2f) {0, offset.y});
}

bool is_in_cam_range(win_t *window, entity_t *entity)
{
    sfVector2f cam_pos = sfView_getCenter(window->cam.view);
    sfVector2f pos = entity->comp_position.position;

    if ((cam_pos.x - pos.x) * (cam_pos.x - pos.x) +
    (cam_pos.y - pos.y) * (cam_pos.y - pos.y) <= RENDER_DISTANCE)
        return true;
    return false;
}
