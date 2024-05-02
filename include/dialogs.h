/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** dialogs
*/

#ifndef DIALOGS_H_
    #define DIALOGS_H_

    #include <SFML/Graphics.h>
    #include "temp.h"

void display_dialogs(win_t *window, world_t *world);
static void mini_update_dialog(int sentence, entity_t *entity, int dialog);
bool temp(win_t *window, world_t *world, entity_t *entity, float x);

#endif /* !DIALOGS_H_ */
