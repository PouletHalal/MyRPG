/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** maps
*/

#ifndef MAPS_
    #define MAPS_

    #include <SFML/Window.h>
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include "tilesets.h"

static const char TEXTURE_PATH[] = "tileset/big_tileset.png";
static const char MAP_FILE[] = "maps/map.conf";
static const char PORTAL_CONF[] = "maps/portals.conf";
static const char NPC_CONF[] = "maps/npcs.conf";

    #define WIDTH 1920
    #define HEIGHT 1080
    #define TILE_WIDTH 32
    #define TILE_HEIGHT TILE_WIDTH
    #define SPRITESHEET_WIDTH 1952
    #define SPRITESHEET_HEIGHT 1088
    #define THRESHOLD 8
    #define MAP_CONF_NB_ARGS 6
    #define PORTAL_CONF_NB_ARGS 9
    #define NPC_CONF_NB_ARGS 11

static const sfVector2f DIALOG_BOX_POS = {WIDTH / 2, HEIGHT * 3 / 4};

typedef struct sprite_s {
    const sfTexture *texture;
    sfSprite *sprite;
    sfVector2f pos;
    sfVector2f scale;
} sprite_t;

typedef struct map_s {
    int nb_layers;
    char *name;
    int **csv_map;
    int priority;
    sfVector2f size;
    sfRenderTexture *map;
    sfTexture *spritesheet;
    sprite_t sprite;
} map_t;

typedef struct map_list_s {
    map_t *maps;
    char *name;
    int nb_layer;
} map_list_t;

typedef struct portal_s {
    int id;
    int origin_id;
    int destination_id;
} portal_t;

tileset_t *init_tilesets(void);
map_list_t **init_map(char const *map_file, tileset_t *tileset_list);
char **my_str_to_word_array(char const *str, char const *separators);
void free_array(char **array);
int len_array(char **array);
#endif
