/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** init_npc
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "temp.h"
#include "error_handling.h"
#include "dialogs.h"
#include "npcs.h"

static int store_dialog(entity_t *entity, char *line, int id)
{
    char **split = NULL;

    if (line == NULL || line[0] == '\n' || line[0] == '\0')
        return 84;
    split = my_str_to_word_array(line, ":\n");
    if (split == NULL || split[0] == NULL)
        return int_display_and_return(84, 2, "Invalid arguments ->", line);
    entity->comp_dialog.text[id] = split;
    entity->comp_dialog.nb_dialogs = id + 1;
    return 0;
}

static void init_mandatories(entity_t *entity)
{
    entity->mask |= COMP_NPC;
    entity->comp_dialog.current_dialog = -1;
    entity->comp_dialog.current_sentence = 0;
    entity->comp_dialog.current_char = 0;
    entity->comp_dialog.substring = NULL;
    entity->comp_dialog.clock = sfClock_create();
    entity->comp_npc.exclamation_display = true;
}

int read_dialogs(world_t *world, entity_t *entity, char *filename)
{
    char **split = my_str_to_word_array(filename, "=\n ");
    FILE *stream = fopen(split[1], "r");
    char *line = NULL;
    size_t len = 0;
    int id = 0;

    if (test_open(stream, split[1]) == -1)
        return 84;
    init_mandatories(entity);
    while (getline(&line, &len, stream) > 0) {
        if (store_dialog(entity, line, id))
            return 84;
        id += 1;
    }
    if (id == 0)
        return int_display_and_return(84, 3, "No dialogs in ", split[1], "\n");
    fclose(stream);
    return 0;
}

static int get_arg(char **split, world_t *world, entity_t *entity, char *line)
{
    for (int i = 0; NPC_ARGS[i].name != NULL; i++) {
        if (strcmp(split[0], NPC_ARGS[i].name) == 0) {
            free_array(split);
            return NPC_ARGS[i].ptr(world, entity, line);
        }
    }
    free_array(split);
    return 0;
}

static void init_npc(world_t *world, char *filename)
{
    FILE *stream = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    int free_slot = find_empty(world);
    entity_t *entity = &world->entity[free_slot];
    char **split = NULL;

    if (test_open(stream, filename) == -1)
        return;
    while (getline(&line, &len, stream) > 0) {
        if (line[0] == '\0' || line[0] == '\n')
            break;
        split = my_str_to_word_array(line, "=\n ");
        entity->mask |= COMP_DIALOG;
        if (get_arg(split, world, entity, line) == 84) {
            entity->mask = COMP_NONE;
            break;
        }
    }
    fclose(stream);
}

void read_npcconf(world_t *world)
{
    FILE *stream = fopen(NPC_CONF, "r");
    char *line = NULL;
    size_t len = 0;

    if (test_open(stream, PORTAL_CONF) == -1)
        return;
    while (getline(&line, &len, stream) > 0) {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        if (line[0] == '\0')
            break;
        init_npc(world, line);
    }
    fclose(stream);
}
