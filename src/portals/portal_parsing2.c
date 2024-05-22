/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** portal_parsing2
*/

#include <stdlib.h>
#include <stdio.h>
#include "temp.h"
#include "player.h"
#include "error_handling.h"

int set_entering_sound(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    entity->comp_portal.comp_sound.sound.buffer = sfSoundBuffer_createFromFile(
    split[1]);
    if (entity->comp_portal.comp_sound.sound.buffer == NULL)
        return int_display_and_return(84, 3, "Invalid sound file: ",
        split[1], "\n");
    entity->comp_portal.comp_sound.sound.sound = sfSound_create();
    sfSound_setBuffer(entity->comp_portal.comp_sound.sound.sound,
    entity->comp_portal.comp_sound.sound.buffer);
    entity->comp_portal.comp_sound.sound.nb_variations = 1;
    sfSound_setVolume(entity->comp_portal.comp_sound.sound.sound, 10);
    return 0;
}

int set_player_spawnpoint(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    char **temp = NULL;
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];
    sfVector2f spawn = {0};

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    temp = my_str_to_word_array(split[1], ", \n\t");
    spawn = (sfVector2f){atof(temp[0]), atof(temp[1])};
    if (spawn.x < 0 || spawn.y < 0 ||
        spawn.x > world->map_list[entity->comp_portal.dest_id]->maps->size.x ||
        spawn.y > world->map_list[entity->comp_portal.dest_id]->maps->size.y)
        return int_display_and_return(84, 3, "Invalid spawnpoint: ", split[1],
        split[2], "\n");
    player->comp_position.spawn = spawn;
    return 0;
}
