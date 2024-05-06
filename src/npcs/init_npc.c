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

static void store_dialog(entity_t *entity, char *line, int id)
{
    char **split = my_str_to_word_array(line, ":\n");

    entity->comp_dialog.text[id] = split;
    entity->comp_dialog.nb_dialogs = id + 1;
}

void read_dialogs(entity_t *entity, char *filename)
{
    FILE *stream = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    int id = 0;

    if (test_open(stream, filename) == -1)
        return;
    entity->comp_dialog.current_dialog = -1;
    entity->comp_dialog.current_sentence = 0;
    while (getline(&line, &len, stream) > 0) {
        store_dialog(entity, line, id);
        id += 1;
    }
    fclose(stream);
}

static void init_comp_dialog(entity_t *entity, char **split)
{
    entity->comp_dialog.is_displayed = false;
    entity->comp_dialog.color = (sfColor){atoi(split[6]), atoi(split[7]),
    atoi(split[8]), 255};
    entity->comp_dialog.sftext = sfText_create();
    entity->comp_dialog.font = sfFont_createFromFile(split[9]);
    sfText_setFont(entity->comp_dialog.sftext, entity->comp_dialog.font);
    entity->comp_dialog.box = sfSprite_create();
    sfSprite_setTexture(entity->comp_dialog.box,
    sfTexture_createFromFile(split[10], NULL), true);
}

void *init_npc(world_t *world, char *line)
{
    char **split = my_str_to_word_array(line, ":\n");
    int free_slot = find_empty(world);
    entity_t *entity;

    if (len_array(split) != NPC_CONF_NB_ARGS)
        return display_and_return(NULL, 2, "Invalid arguments nbr ->", line);
    entity = &world->entity[free_slot];
    *entity = (entity_t) {0};
    entity->entity = free_slot;
    entity->mask |= COMP_DIALOG | COMP_POSITION | COMP_HITBOX;
    init_comp_position(entity, (sfVector2f) {atof(split[0]), atof(split[1])});
    init_comp_render(entity, world, atoi(split[3]),
    entity->comp_position.position);
    init_comp_hitbox(entity, (sfVector2f) {atof(split[0]), atof(split[1])});
    init_comp_dialog(entity, split);
    read_dialogs(entity, split[5]);
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
    fclose(stream);
}
