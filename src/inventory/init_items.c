/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** init_items
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"
#include "error_handling.h"
#include "temp.h"
#include "items_parsing.h"

void create_item(world_t *world, sfVector2f pos, int item_id)
{
    int free_slot = find_empty(world);
    entity_t *entity = &world->entity[free_slot];

    entity->entity = free_slot;
    entity->mask |= COMP_ITEM;
    entity->mask |= COMP_STAT;
    entity->comp_stat = *(&world->item_list.items[item_id].stats);
    entity->comp_item = *(&world->item_list.items[item_id]);
    entity->comp_item.id_in_world = free_slot;
    init_comp_render(entity, world, &world->animations
    [world->item_list.items[item_id].animation_id], pos);
    init_comp_position(entity, pos, world->map_id);
}

static int get_item_arg(world_t *world, comp_item_t *item, char *line,
    char **split)
{
    if (split == NULL || split[0] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid line: ", line, "\n");
    }
    for (int i = 0; ITEM_FLAGS[i].name != NULL; i++) {
        if (strcmp(split[0], ITEM_FLAGS[i].name) == 0 &&
            ITEM_FLAGS[i].ptr != NULL) {
            return ITEM_FLAGS[i].ptr(world, item, line);
        }
    }
    return 0;
}

int is_eof(char *line)
{
    if (line == NULL)
        return 1;
    if (line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';
    if (line[0] == '\0')
        return 1;
    return 0;
}

static void init_mandatory_item(world_t *world, int item_id)
{
    world->item_list.items[item_id].stats = (comp_stat_t) {0};
    world->item_list.items[item_id].is_picked = false;
    world->item_list.items[item_id].id = item_id;
}

static int init_item(world_t *world, char *filename, int item_id)
{
    FILE *stream = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    char **split = NULL;

    if (test_open(stream, filename) == -1)
        return 84;
    while (getline(&line, &len, stream) > 0) {
        if (is_eof(line) == 1)
            break;
        split = my_str_to_word_array(line, "= \n\t");
        if (split == NULL)
            return int_display_and_return(84, 3, "Invalid line: ", line, "\n");
        if (get_item_arg(world, &world->item_list.items[item_id], line, split))
            return 84;
        free_array(split);
    }
    return fclose(stream);
}

static void remove_last_char(char *line)
{
    if (line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';
}

int read_items_conf(world_t *world)
{
    FILE *stream = fopen(ITEM_CONF, "r");
    char *line = NULL;
    size_t len = 0;

    if (openning_and_reading(stream, ITEM_CONF, &line) == -1)
        return int_display_and_return(84, 1, "Invalid file\n");
    world->item_list.nb_items = atoi(line);
    if (world->item_list.nb_items <= 0)
        return int_display_and_return(84, 3, "Invalid items nb: ", line, "\n");
    world->item_list.items = calloc(world->item_list.nb_items,
        sizeof(comp_item_t));
    for (int item_id = 0; getline(&line, &len, stream) > 0; ++item_id) {
        remove_last_char(line);
        if (line[0] == '\0')
            break;
        init_mandatory_item(world, item_id);
        if (init_item(world, line, item_id) == 84)
            return 84;
    }
    return fclose(stream);
}
