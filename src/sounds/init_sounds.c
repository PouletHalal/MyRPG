/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** sounds
*/

#include <SFML/Audio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ecs.h"
#include "sounds.h"
#include "error_handling.h"

static void load_sound(sounds_t *sound, char *line, int nb_sounds)
{
    if (line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';
    sound->buffer = sfSoundBuffer_createFromFile(line);
    sound->sound = sfSound_create();
    sound->nb_variations = nb_sounds;
    sfSound_setBuffer(sound->sound, sound->buffer);
}

static sound_list_t *init_sound(char *line, FILE *stream, size_t size)
{
    sound_list_t *sound = malloc(sizeof(sound_list_t));
    char **split = my_str_to_word_array(line, ":\n");

    if (sound == NULL)
        return display_and_return(NULL, 1, "Fail malloc\n");
    sound->name = strdup(split[0]);
    sound->nb_sounds = atoi(split[1]);
    sound->sounds = malloc(sizeof(sounds_t) * sound->nb_sounds);
    sound->clock = sfClock_create();
    if (sound->sounds == NULL)
        return display_and_return(NULL, 1, "Fail malloc\n");
    for (int i = 0; i < sound->nb_sounds; ++i) {
        if (getline(&line, &size, stream) < 0)
            return display_and_return(NULL, 1, "Fail reading line\n");
        load_sound(&sound->sounds[i], line, sound->nb_sounds);
    }
    return sound;
}

sound_list_t **init_sounds(sound_list_t **sounds, char const *sounds_file)
{
    FILE *stream = fopen(sounds_file, "r");
    char *line = NULL;
    size_t size = 0;
    int nb_sounds = 0;

    if (openning_and_reading(stream, sounds_file, &line))
        return NULL;
    nb_sounds = atoi(line);
    if (nb_sounds <= 0)
        return display_and_return(NULL, 2, "Invalid nbr of sounds ->", line);
    sounds = calloc(nb_sounds + 1, sizeof(sound_list_t *));
    for (int i = 0; i < nb_sounds; ++i) {
        if (getline(&line, &size, stream) < 0)
            return display_and_return(NULL, 1, "Fail reading line\n");
        sounds[i] = init_sound(line, stream, size);
        if (sounds[i] == NULL)
            return NULL;
    }
    sounds[nb_sounds] = NULL;
    return sounds;
}
