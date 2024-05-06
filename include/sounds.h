/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** sounds
*/

#ifndef SOUNDS_H_
    #define SOUNDS_H_

    #include <SFML/Audio.h>

    #define NAME_SIZE 256

static const char SOUNDS_FILE[] = "maps/sounds.conf";

typedef struct sound_ids_s {
    char name[NAME_SIZE];
    int id;
} sound_ids_t;

typedef struct sounds_s {
    int nb_variations;
    sfSoundBuffer *buffer;
    sfSound *sound;
} sounds_t;

typedef struct sound_list_s {
    int nb_sounds;
    int id;
    char *name;
    sounds_t *sounds;
    sfClock *clock;
} sound_list_t;

typedef struct music_s {
    int id;
    char *name;
    sfMusic *music;
} music_t;


sound_list_t **init_sounds(sound_list_t **sound, char const *sounds_file);

#endif /* !SOUNDS_H_ */
