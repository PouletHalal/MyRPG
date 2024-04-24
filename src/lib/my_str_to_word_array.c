/*
** EPITECH PROJECT, 2023
** My str to word array
** File description:
** my str to word array
*/

#include <stdlib.h>

static int test_separator(char c, char const *sep)
{
    if (c == '\0')
        return 1;
    for (size_t i = 0; sep[i] != '\0'; ++i)
        if (sep[i] == c)
            return 1;
    return 0;
}

static char *get_word(size_t start, size_t end, char const *str)
{
    char *string = malloc(sizeof(char) * (end - start + 1));

    if (string == NULL)
        return NULL;
    string[end - start] = '\0';
    for (size_t i = 0; i < end - start; i++)
        string[i] = str[start + i];
    return string;
}

static void get_array(char **res, char const *str, char const *sep)
{
    size_t start = 0;
    size_t end = 0;
    size_t str_nb = 0;

    for (end = 0; str[end] != '\0'; ++end) {
        if (test_separator(str[end], sep) == 1 && start != end) {
            res[str_nb] = get_word(start, end, str);
            str_nb++;
            start = end + 1;
        }
        if (test_separator(str[end], sep) == 1 && start == end)
            start++;
    }
    if (start != end) {
        res[str_nb] = get_word(start, end, str);
        str_nb++;
    }
    res[str_nb] = NULL;
    return;
}

int array_len(char **array)
{
    int len = 0;

    if (array == NULL)
        return 0;
    while (array[len] != NULL)
        len += 1;
    return len;
}

void free_array(char **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; ++i)
        free(array[i]);
    free(array);
}

char **my_str_to_word_array(char const *str, char const *separators)
{
    char **res = NULL;
    size_t str_nb = 0;
    int type = 0;

    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (test_separator(str[i], separators) == 0 && type == 0) {
            str_nb++;
            type = 1;
        }
        if (test_separator(str[i], separators) == 1 && type == 1)
            type = 0;
    }
    res = malloc(sizeof(char *) * (str_nb + 1));
    if (res == NULL)
        return NULL;
    get_array(res, str, separators);
    for (size_t i = 0; i < str_nb; ++i)
        if (res[i] == NULL)
            return NULL;
    return res;
}
