/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** error_handling
*/

#ifndef ERROR_HANDLING_H_
    #define ERROR_HANDLING_H_

    #include "temp.h"

void *display_and_return(void *ptr, int nb, ...);
int int_display_and_return(int return_value, int nb, ...);
int openning_and_reading(FILE *stream, char const *filename, char **line);
int test_open(FILE *stream, char const *filename);
int close_and_return(world_t *world, win_t *window, int nb);

#endif /* !ERROR_HANDLING_H_ */
