/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** my_rpg
*/

#ifndef MOUSE_H_
    #define MOUSE_H_

    #include "ecs.h"
    #include "player.h"
    #include "temp.h"

void init_mouse(world_t *world, win_t *window);
void move_mouse(world_t *world, win_t *window);

#endif /* !MOUSE_H_ */
