/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** portal_parsing2
*/

#include <stdlib.h>
#include <stdio.h>
#include "temp.h"
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
    sfSound_setVolume(entity->comp_portal.comp_sound.sound.sound, 20);
    return 0;
}
