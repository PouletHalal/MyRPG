/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Main file
*/

#include <stdlib.h>
#include <time.h>
#include "temp.h"
#include "maps.h"
#include "camera.h"
#include "rendering.h"
#include "error_handling.h"
#include "sounds.h"

int find_empty(world_t *world)
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

static void init_all(win_t *window, world_t *world)
{
    sfVector2f position_player = {500, 150};
    sfVector2f position_mob = {800, 150};

    init_textures(world);
    init_entity(world, ANIM_PROTA_IDLE, position_player);
    for (int i = 0; i < 10; i++){
        init_mob(world, ANIM_MOB_RUN, position_mob);
        position_mob.x += 60;
    }
    init_cam(window, world);
    read_portalconf(world);
    read_npcconf(world);
}

int main(void)
{
    world_t world = {0};
    win_t *window = create_win();
    sfClock *clock = sfClock_create();
    tileset_t *tileset_list = init_tilesets();
    map_list_t **map_list = init_map(MAP_FILE, tileset_list);
    sound_list_t **sound_list = init_sounds(sound_list, SOUNDS_FILE);

    if (map_list == NULL || sound_list == NULL)
        return close_and_return(window, 84);
    srand(time(NULL));
    world.map_list = map_list;
    world.sound_list = sound_list;
    init_all(window, &world);
    while (sfRenderWindow_isOpen(window->window)) {
        refresh_world(&world, clock, window);
        render_window(window, &world);
        refresh_sounds(&world, clock);
    }
    return close_and_return(window, 0);
}
