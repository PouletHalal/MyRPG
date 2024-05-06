/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** init_portals
*/

#include <stdlib.h>
#include <stdio.h>
#include "temp.h"
#include "error_handling.h"

static bool invalid_coords(world_t *world, char **split)
{
    if (atof(split[4]) < 0 ||
        atof(split[4]) > world->map_list[world->map_id]->maps->size.x ||
        atof(split[5]) < 0 ||
        atof(split[5]) > world->map_list[world->map_id]->maps->size.y) {
        display_and_return(NULL, 4, "Invalid portal coordinates",
        split[4], split[5], "\n");
        return true;
    }
    return false;
}

static bool invalid_id(world_t *world, char **split)
{
    if (atof(split[2]) < 0) {
        display_and_return(NULL, 3, "Invalid map id",
        split[2], "\n");
        return true;
    }
    if (atof(split[3]) < 0) {
        display_and_return(NULL, 3, "Invalid portal id",
        split[3], "\n");
        return true;
    }
    return false;
}

void *init_portal(world_t *world, char *line)
{
    char **split = my_str_to_word_array(line, ":");
    int free_slot = find_empty(world);
    entity_t *entity;

    if (len_array(split) != PORTAL_CONF_NB_ARGS)
        return display_and_return(NULL, 2, "Invalid arguments nbr ->", line);
    if (invalid_id(world, split) || invalid_coords(world, split))
        return NULL;
    entity = &world->entity[free_slot];
    *entity = (entity_t) {0};
    entity->entity = free_slot;
    entity->mask |= COMP_PORTAL | COMP_POSITION | COMP_HITBOX;
    init_comp_portal(entity, split);
    init_comp_render(entity, world, ANIM_PORTAL_GREEN,
    entity->comp_position.position);
}

void init_comp_portal(entity_t *entity, char **split)
{
    entity->comp_position.position = (sfVector2f){atof(split[0]),
    atof(split[1])};
    entity->comp_portal.origin_id = atoi(split[2]);
    entity->comp_position.world = atoi(split[2]);
    entity->comp_portal.dest_id = atoi(split[3]);
    entity->comp_portal.dest_pos = (sfVector2f){atof(split[4]),
    atof(split[5])};
    entity->comp_hitbox.hitbox = (sfFloatRect)
    {-atof(split[6]) / 2., -atof(split[7]) / 2.,
    atof(split[6]), atof(split[7])};
}

void read_portalconf(world_t *world)
{
    FILE *stream = fopen(PORTAL_CONF, "r");
    char *line = NULL;
    size_t len = 0;

    if (test_open(stream, PORTAL_CONF) == -1)
        return;
    while (getline(&line, &len, stream) > 0) {
        init_portal(world, line);
    }
    fclose(stream);
}
