/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** dialogs
*/

#ifndef DIALOGS_H_
    #define DIALOGS_H_

    #include "window.h"
    #include "world.h"



void display_dialogs(win_t *window, world_t *world);
void update_dialog(win_t *window, world_t *world, entity_t *entity);
int read_dialogs(world_t *world, entity_t *entity, char *filename);
void update_substring(entity_t *entity, int dialog, int sentence);
void no_input_dialogs(win_t *window, world_t *world);
void sys_npc(win_t *window, world_t *world, entity_t *player);
#endif /* !DIALOGS_H_ */
