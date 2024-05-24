/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Start file
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "temp.h"
#include "error_handling.h"
#include "spell_parsing.h"

int get_effect_id(char *name)
{
    for (int i = 0; EFFECT_NAMES[i].name != NULL; i++) {
        if (strcmp(name, EFFECT_NAMES[i].name) == 0)
            return i;
    }
    return 0;
}

int get_move_id(char *name)
{
    for (int i = 0; MOVE_NAMES[i].name != NULL; i++) {
        if (strcmp(name, MOVE_NAMES[i].name) == 0)
            return MOVE_NAMES[i].move_type;
    }
    return 0;
}

int get_target_id(char *name)
{
    for (int i = 0; TARGET_NAMES[i].name != NULL; i++) {
        if (strcmp(name, TARGET_NAMES[i].name) == 0) {
            return TARGET_NAMES[i].target;
        }
    }
    return 0;
}

static int get_spell_arg(world_t *world, comp_spell_t *spell, char *line,
    char **split)
{
    for (int i = 0; SPELL_FLAGS[i].name != NULL; i++) {
        if (strcmp(split[0], SPELL_FLAGS[i].name) == 0 &&
            SPELL_FLAGS[i].ptr != NULL) {
            return SPELL_FLAGS[i].ptr(world, spell, line);
        }
    }
    return 0;
}

static int init_spell(world_t *world, char *filename, int spell_id)
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
        if (get_spell_arg(world, &world->spell_list[spell_id], line, split))
            return 84;
        free_array(split);
    }   
    return fclose(stream);
}

int read_spells_conf(world_t *world)
{
    FILE *stream = fopen(SPELL_CONF, "r");
    char *line = NULL;
    size_t len = 0;
    int spell_id = 0;

    if (test_open(stream, SPELL_CONF) == -1)
        return int_display_and_return(84, 1, "Invalid file\n");
    world->spell_list = NULL;
    for (spell_id = 0; getline(&line, &len, stream) > 0; ++spell_id) {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        if (line[0] == '\0')
            break;
        world->spell_list = realloc(world->spell_list,
            sizeof(comp_spell_t) * (spell_id + 1));
        world->spell_list[spell_id] = (comp_spell_t) {0};
        if (init_spell(world, line, spell_id) == 84)
            return 84;
    }
    world->spell_list = realloc(world->spell_list,
        sizeof(comp_spell_t) * (spell_id + 1));
    world->spell_list[spell_id].animation = NULL;
    return fclose(stream);
}


void create_spell(world_t *world, sfVector2f position, int spell_id)
{
    int free = find_empty(world);
    entity_t *entity = NULL;
    comp_spell_t *spell = &world->spell_list[spell_id];

    if (free == -1)
        return;
    if (world->map_list[world->map_id]->can_attack == sfFalse)
        return;
    entity = &world->entity[free];
    *entity = (entity_t){0};
    entity->entity = free;
    init_comp_position(entity, position, world->map_id);
    init_comp_render(entity, world, &world->animations[spell->index], position);
    init_comp_hitbox(entity, position);
    entity->mask |= COMP_SPELL;
    entity->comp_hitbox.do_collide = sfFalse;
    entity->comp_spell = *spell;
    if (entity->comp_spell.move_type == DIRECT){
        follow_enemy(entity, get_closest(entity, world));
        entity->comp_position.vector_lenght[0] = 9999999;
    }
}
