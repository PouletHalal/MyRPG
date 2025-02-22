/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** tilesets
*/

#ifndef TILESETS_H_
    #define TILESETS_H_

    #include <SFML/Graphics.h>

    #define NAME_MAX 256
    #define NB_ARGS 6

static const char tileset_conf[] = "tileset/tilesets.conf";

typedef struct tileset_s {
    int nb_tileset;
    char *name;
    sfTexture *tileset;
    sfVector2f size;
    sfVector2f tile_size;
} tileset_t;


#endif /* !TILESETS_H_ */
