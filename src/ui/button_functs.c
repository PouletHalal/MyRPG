/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** my_rpg
*/

#include "world.h"
#include "ui.h"
#include <stdio.h>
#include "string.h"

void quit(win_t *window, world_t *world)
{
    sfRenderWindow_close(window->window);
}

void mute_unmute_music(win_t *window, world_t *world)
{
    if (world->music_volume == 100) {
        world->music_volume = 0;
        return;
    }
    if (world->music_volume == 0) {
        world->music_volume = 100;
        return;
    }
}

void mute_unmute_audio(win_t *window, world_t *world)
{
    if (world->sound_volume == 100) {
        world->sound_volume = 0;
        return;
    }
    if (world->sound_volume == 0) {
        world->sound_volume = 100;
        return;
    }
}

int get_button_func_from_func_name(char *func_name)
{
    for (int i = 0; BUTTONS_FUNCS[i].callback != NULL && BUTTONS_FUNCS[i].name
        != NULL; i++) {
        if (strcmp(func_name, BUTTONS_FUNCS[i].name) == 0)
            return i;
    }
    return -1;
}
