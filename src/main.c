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
#include "player.h"

int find_empty(world_t *world)
{
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if (world->entity[i].mask == COMP_NONE) {
            world->entity[i] = (entity_t) {0};
            world->entity[i].entity = i;
            return i;
        }
    return -1;
}

static win_t *create_win(void)
{
    win_t *window = malloc(sizeof(win_t));

    window->mode = (sfVideoMode){WIDTH, HEIGHT, 32};
    window->style = (sfUint32){sfClose};
    window->window = sfRenderWindow_create(window->mode, "SFML window", sfClose
    | sfResize, NULL);
    window->windows_scale = (sfVector2f) {1, 1};
    init_view(window);
    return window;
}

static void init_all(win_t *window, world_t *world)
{
    sfVector2f position_player = {636, 489};

    init_textures(world);
    init_entity(world, ANIM_PROTA_IDLE, position_player);
    read_npcconf(world);
    read_portalconf(world);
    read_items_conf(world);
    read_mobconf(world);
    init_cam(window, world, &world->entity[find_comp(world, COMP_PLAYER)]);
}

void full_screen(world_t *world, win_t *window)
{
    if (world->key_pressed[sfKeyF11]) {
        world->key_pressed[sfKeyF11] = false;
        sfRenderWindow_destroy(window->window);
        if (window->fullscreen)
            window->style = (sfUint32){sfClose | sfResize | sfFullscreen};
        else
            window->style = (sfUint32){sfClose | sfResize};
        window->window = sfRenderWindow_create(window->mode, "SFML window",
        window->style, NULL);
        sfRenderWindow_setMouseCursorVisible(window->window, sfFalse);
        window->fullscreen = !window->fullscreen;
    }
}

static int init_empty_world(world_t *world)
{
    tileset_t *tileset_list = init_tilesets();
    sound_list_t **sound_list = init_sounds(sound_list, SOUNDS_FILE);

    world->map_list = init_map(MAP_FILE, tileset_list);
    world->sound_list = sound_list;
    world->map_id = INTRO;
    for (int i = 0; i < ANIM_END; ++i)
        world->texture_list[i] = sfTexture_createFromFile(
            animation_list[i].filename, NULL);
    for (int i = 0; i < NB_KEYS; ++i) {
        world->key_down[i] = sfFalse;
        world->key_pressed[i] = sfFalse;
    }
    for (int i = 0; i < ENTITY_COUNT; ++i)
        world->entity[i] = (entity_t) {0};
    if (world->map_list == NULL || sound_list == NULL)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int main(void)
{
    win_t *window = create_win();
    world_t *world = malloc(sizeof(world_t));
    sfClock *clock = sfClock_create();

    if (init_empty_world(world) == EXIT_FAILURE)
        return close_and_return(world, window, 84);
    srand(time(NULL));
    init_all(window, world);
    while (sfRenderWindow_isOpen(window->window)) {
        refresh_world(world, clock, window);
        render_window(window, world);
        refresh_sounds(world, clock);
    }
    return close_and_return(world, window, 0);
}
