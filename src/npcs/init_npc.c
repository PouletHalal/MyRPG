/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** init_npc
*/

#include <stdlib.h>
#include <stdio.h>
#include "temp.h"
#include "error_handling.h"

void *init_npc(world_t *world, char *line)
{
    char **split = my_str_to_word_array(line, ":");
    int free_slot = find_empty(world);
    entity_t *entity;

    if (len_array(split) != NPC_CONF_NB_ARGS)
        return display_and_return(NULL, 2, "Invalid arguments nbr ->", line);
    entity = &world->entity[free_slot];
    *entity = (entity_t) {0};
    entity->entity = free_slot;
    entity->mask |= COMP_DIALOG | COMP_POSITION | COMP_HITBOX;
    entity->comp_position.position.x = atof(split[0]);
    entity->comp_position.position.y = atof(split[1]);
    init_comp_render(entity, world, atoi(split[3]),
    entity->comp_position.position);
    init_hitbox(entity, (sfVector2f) {atof(split[0]), atof(split[1])});
}

void read_npcconf(world_t *world)
{
    FILE *stream = fopen(NPC_CONF, "r");
    char *line = NULL;
    size_t len = 0;

    if (test_open(stream, PORTAL_CONF) == -1)
        return;
    while (getline(&line, &len, stream) > 0) {
        init_npc(world, line);
    }
}

