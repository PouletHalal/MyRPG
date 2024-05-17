/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** parsing
*/

#ifndef PARSING_H_
    #define PARSING_H_

    #include "ecs.h"

typedef struct ptr_funcs {
    char *name;
    int (*ptr)(world_t *world, entity_t *entity, char *args);
} ptr_func_t;

ptr_func_t MAP_FLAGS[] =
{
    {"nb_layers", NULL},
    {"music", NULL},
    {"layer", NULL},
    {NULL, NULL}
}

#endif /* !PARSING_H_ */
