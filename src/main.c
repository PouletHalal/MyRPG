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
#include "mouse.h"
#include "hud.h"
#include "ui.h"

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
    sfRenderWindow_setFramerateLimit(window->window, 60);
    window->sound = 100;
    window->music = 100;
    sfRenderWindow_setMouseCursorVisible(window->window, sfFalse);
    return window;
}

static void read_configs(world_t *world, win_t *window)
{
    sfVector2f position_player = {636, 489};
    int anim_index = get_anim_id(world, "prota_idle");

    init_entity(world, &world->animations[anim_index],
    position_player);
    read_effect_conf(world);
    read_spells_conf(world);
    read_items_conf(world);
    init_healthbar(world);
    init_xpbar(world);
    init_manabar(world);
    read_npcconf(world);
    read_portalconf(world);
    read_mobconf(world);
    read_partconf(world);
    init_cam(window, world, &world->entity[find_comp(world, COMP_PLAYER)]);
    init_mouse(world, window);
    read_ui_conf(world);
}

static void init_all(win_t *window, world_t *world)
{
    sfVector2f position_player = {636, 489};
    int anim_index = get_anim_id(world, "prota_idle");

    if (anim_index == -1) {
        int_display_and_return(0, 2, "Player Animation not found", "\n");
        anim_index = 0;
    }
    read_configs(world, window);
    world->is_paused = true;
    world->ui_id = UI_MAIN;
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
        sfRenderWindow_setFramerateLimit(window->window, 60);
        window->fullscreen = !window->fullscreen;
    }
}

static void init_inputs(world_t *world)
{
    world->mouse_right_pressed = false;
    world->mouse_left_pressed = false;
    for (int i = 0; i < NB_KEYS; ++i) {
        world->key_down[i] = sfFalse;
        world->key_pressed[i] = sfFalse;
    }
}

static int init_empty_world(world_t *world)
{
    tileset_t *tileset_list = init_tilesets();
    sound_list_t **sound_list = init_sounds(sound_list, SOUNDS_FILE);

    read_animconf(world);
    init_textures(world);
    world->light_sprite = create_light(200, (sfColor) {255, 255, 153, 255});
    world->map_list = init_map(MAP_FILE, tileset_list);
    world->sound_list = sound_list;
    world->map_id = INTRO;
    init_inputs(world);
    for (int i = 0; world->map_list[i] != NULL; ++i)
        world->map_list[i]->has_cam = false;
    for (int i = 0; i < ENTITY_COUNT; ++i)
        world->entity[i] = (entity_t){0};
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
    while (sfRenderWindow_isOpen(window->window)){
        refresh_world(world, clock, window);
        render_window(window, world);
        refresh_sounds(world, clock);
        move_mouse(world, window);
    }
    return close_and_return(world, window, 0);
}
