/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** sounds_gestion
*/

#include <SFML/Audio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "temp.h"
#include "sounds.h"
#include "player.h"
#include "maps.h"

static bool is_playing(world_t *world, int sound_id)
{
    int size = 0;

    for (; world->sound_list[size] != NULL; size++);
    if (sound_id >= size)
        return true;
    for (int i = 0; i < world->sound_list[sound_id]->sounds[0].nb_variations;
        i++)
        if (sfSound_getStatus(world->sound_list[sound_id]->sounds[i].sound) ==
            sfPlaying)
            return true;
    return false;
}

void refresh_sounds(world_t *world, sfClock *clock)
{
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];
    sfVector2f pos = player->comp_position.position;
    int **sound_map = get_layer(world->map_list[world->map_id], "sounds");
    int x = ((pos.x) / TILE_WIDTH);
    int y = ((pos.y) / TILE_HEIGHT);
    int random = rand() % 5;

    if ((player->comp_position.velocity->x == 0 &&
        player->comp_position.velocity->y == 0) || sound_map == NULL)
        return;
    if (is_playing(world, sound_map[y][x]))
        return;
    if (sfClock_getElapsedTime(world->sound_list[sound_map[y][x]]->clock)
        .microseconds >= 500000) {
        sfClock_restart(world->sound_list[sound_map[y][x]]->clock);
    } else
        return;
    sfSound_play(world->sound_list[sound_map[y][x]]->sounds[random].sound);
}
