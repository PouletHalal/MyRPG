/*
** EPITECH PROJECT, 2024
** My radar
** File description:
** Start file
*/

#include <stdlib.h>
#include <time.h>
#include "temp.h"

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
    sfVideoMode mode = {1920, 1080, 32};

    window->window = sfRenderWindow_create(mode, "SFML window",
    sfResize | sfClose, NULL);
    window->windows_scale = (sfVector2f) {1, 1};
    return window;
}

static void refresh_world(world_t *world, sfClock *clock, win_t *window)
{
    if (sfClock_getElapsedTime(clock).microseconds / 1e6 < 1. / 60.)
        return;
    sfClock_restart(clock);
    sys_input_and_event(world, window);
    sys_position(world);
    sys_player(world);
    sys_render(world);
}

static void render_window(win_t *window, world_t *world)
{
    sfRenderWindow_clear(window->window, sfBlack);
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if (world->entity[i].mask & COMP_RENDER == COMP_RENDER && world->entity[i].comp_render.is_visible == true)
            sfRenderWindow_drawSprite(window->window, world->entity[i].comp_render.sprite, NULL);
    sfRenderWindow_display(window->window);
}

int main(void)
{
    world_t world = {0};
    win_t *window = create_win();
    sfClock *clock = sfClock_create();
    int ran = 17;

    for (int i = 0; i < TXT_END; ++i)
        world.texture_list[i] = sfTexture_createFromFile(texture_file[i], NULL);
    srand(time(NULL));
    create_perso_style_insane(&world.entity[0], world.texture_list[ran], &mob_list[ran], &world);
    while (sfRenderWindow_isOpen(window->window)) {
        refresh_world(&world, clock, window);
        render_window(window, &world);
    }
    sfRenderWindow_destroy(window->window);
    free(window);
    return 0;
}
