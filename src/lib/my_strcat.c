/*
** EPITECH PROJECT, 2023
** strcat
** File description:
** j'aime bien les chats
*/

#include <stdlib.h>
#include <string.h>
#include "maps.h"

char *my_strcat(char *dest, char *src)
{
    int len = strlen(dest);
    int lensrc = strlen(src);
    char *res = malloc(sizeof(char) * (len + lensrc + 1));
    int i = 0;
    int j = 0;

    for (i; i < lensrc; i ++)
        res[i] = src[i];
    for (i; i < lensrc + len; i ++) {
        res[i] = dest[j];
        j += 1;
    }
    res[i] = '\0';
    return res;
}
