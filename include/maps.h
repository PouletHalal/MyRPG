/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** maps
*/

#ifndef MAPS_
    #define MAPS_

    #include <SFML/Audio.h>
    #include "tilesets.h"

static const char TEXTURE_PATH[] = "tileset/big_tileset.png";
static const char MAP_FILE[] = "maps/map.conf";
static const char PORTAL_CONF[] = "maps/portals.conf";
static const char NPC_CONF[] = "maps/npcs.conf";
static const char ITEM_CONF[] = "maps/items.conf";
static const char MOB_CONF[] = "maps/mobs.conf";
static const char PART_CONF[] = "maps/part.conf";

    #define WIDTH 1920
    #define HEIGHT 1080
    #define TILE_WIDTH 32
    #define TILE_HEIGHT TILE_WIDTH
    #define SPRITESHEET_WIDTH 1952
    #define SPRITESHEET_HEIGHT 1088
    #define THRESHOLD 8
    #define MAP_CONF_NB_ARGS 6
    #define PORTAL_CONF_NB_ARGS 9
    #define NPC_CONF_NB_ARGS 12

static const sfVector2f DIALOG_BOX_POS = {WIDTH / 2, HEIGHT * 2 / 3};

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
    sfVector2f tile_size;
} map_t;

typedef struct map_list_s {
    sfBool has_cam;
    sfBool display_hud;
    sfBool can_attack;
    int nb_layer;
    sfVector2f cam_size;
    char *name;
    sfMusic *music;
    map_t *maps;
} map_list_t;

typedef struct portal_s {
    int id;
    int origin_id;
    int destination_id;
} portal_t;

tileset_t *init_tilesets(void);
map_list_t **init_map(char const *map_file, tileset_t *tileset_list);
int **get_layer(map_list_t *map_list, char const *name);
void parse_map(map_t *map, char const *name, tileset_t *tileset);
#endif
