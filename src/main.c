/*
** EPITECH PROJECT, 2024
** My radar
** File description:
** Start file
*/

#include <stdlib.h>
#include <time.h>
#include "temp.h"
#include "maps.h"
#include "camera.h"
#include "rendering.h"
#include "error_handling.h"

static int find_empty(world_t *world)
{
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if (world->entity[i].mask == COMP_NONE)
            return i;
    return -1;
}

static win_t *create_win(void)
{
    win_t *window = malloc(sizeof(win_t));
    sfVideoMode mode = {WIDTH, HEIGHT, 32};

    window->window = sfRenderWindow_create(mode, "SFML window", sfClose, NULL);
    window->windows_scale = (sfVector2f) {1, 1};
    init_view(window);
    return window;
}

int main(void)
{
    world_t world = {0};
    win_t *window = create_win();
    sfClock *clock = sfClock_create();
    int ran = 17;
    tileset_t *tileset_list = init_tilesets();
    map_list_t **map_list = init_map(MAP_FILE, tileset_list);

    if (map_list == NULL)
        return close_and_return(window, 84);
    srand(time(NULL));
    init_textures(&world);
    init_entity(&world.entity[0], world.texture_list[ran],
        &mob_list[ran], &world);
    init_cam(window, &world);
    while (sfRenderWindow_isOpen(window->window)) {
        refresh_world(&world, clock, window, map_list[world.map_id]);
        render_window(window, &world, map_list[world.map_id]);
    }
    return close_and_return(window, 0);
}
