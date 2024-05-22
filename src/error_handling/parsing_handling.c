/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** parsing_handling
*/

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "maps.h"
#include "tilesets.h"
#include "temp.h"
#include "error_handling.h"

void *display_and_return(void *ptr, int nb, ...)
{
    va_list args = {0};
    char *output = NULL;

    va_start(args, nb);
    output = va_arg(args, char *);
    while (nb != 0) {
        dprintf(2, "%s", output);
        output = va_arg(args, char *);
        nb --;
    }
    va_end(args);
    return ptr;
}

int int_display_and_return(int return_value, int nb, ...)
{
    va_list args = {0};
    char *output = NULL;

    va_start(args, nb);
    output = va_arg(args, char *);
    while (nb != 0) {
        dprintf(2, "%s", output);
        output = va_arg(args, char *);
        nb --;
    }
    va_end(args);
    return return_value;
}

int test_open(FILE *stream, char const *filename)
{
    if (stream == NULL) {
        display_and_return(NULL, 3, "Fail openning: ", filename, "\n");
        return -1;
    }
    return 0;
}

int openning_and_reading(FILE *stream, char const *filename, char **line)
{
    size_t size = 0;

    if (stream == NULL) {
        display_and_return(NULL, 3, "Fail openning: ", filename, "\n");
        return -1;
    }
    if (getline(line, &size, stream) < 0) {
        display_and_return(NULL, 1, "Fail reading line\n");
        return -1;
    }
    return 0;
}

int close_and_return(world_t *world, win_t *window, int nb)
{
    sfRenderWindow_close(window->window);
    sfRenderWindow_destroy(window->window);
    free(window);
    free(world);
    return nb;
}
