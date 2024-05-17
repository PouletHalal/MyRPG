/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** init_animations
*/

#include "temp.h"
#include "maps.h"


void init_animations(world_t *world)
{
    FILE *stream = fopen(TEXTURES_PATH, "r");
    char *line = NULL;
    size_t len = 0;

    for (int i = 0; getline(&line, &len, stream) != -1; i++) {
        world->texture_list[i] = sfTexture_createFromFile(line, NULL);
    }
}
