/*
** EPITECH PROJECT, 2024
** main
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "temp.h"

void add_to_memory(memory_t **memory, entity_t *entity)
{
    memory_t *new_memory = malloc(sizeof(memory_t));

    new_memory->entity_seen = entity;
    new_memory->next = *memory;
    *memory = new_memory;
}

bool is_in_memory(memory_t **start_memory, entity_t *entity)
{
    memory_t *memory = *start_memory;

    while (memory != NULL){
        if (memory->entity_seen == entity)
            return true;
        memory = memory->next;
    }
    return false;
}

void free_memory(memory_t *memory)
{
    if (memory == NULL)
        return;
    if (memory->next != NULL)
        free_memory(memory->next);
    free(memory);
}
