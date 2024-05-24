/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** ui
*/

#ifndef UI_H_
    #define UI_H_

    #include "world.h"

enum UI_MASKS {
    UI_NONE = 0,
    UI_MAIN = 1 << 0,
    UI_PAUSE = 1 << 1,
    UI_SETTINGS = 1 << 2,
};

typedef struct UI_MASKS_NAMES {
    int mask;
    char *name;
} ui_masks_names_t;

static const ui_masks_names_t UI_MASKS_NAMES[] = {
    {UI_NONE, "none"},
    {UI_MAIN, "main"},
    {UI_PAUSE, "pause"},
    {UI_SETTINGS, "settings"},
    {0, NULL}
};

int get_ui_mask(char *name);
void sys_ui(win_t *win, world_t *world);
#endif /* !UI_H_ */
