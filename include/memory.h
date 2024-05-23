/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** memory
*/

#ifndef MEMORY_H_
    #define MEMORY_H_

    #include "spell.h"
    #include "world.h"

void free_memory(memory_t *memory);
bool is_in_memory(memory_t **start_memory, entity_t *entity);
void add_to_memory(memory_t **memory, entity_t *entity);


#endif /* !MEMORY_H_ */
