/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** my_rpg
*/

#include "ecs.h"
#include "player.h"
#include "temp.h"
#include "rendering.h"
#include "world.h"

void move_mouse(world_t *world, win_t *window)
{
    int mouse_slot = find_comp(world, COMP_MOUSE);
    entity_t *mouse = &world->entity[mouse_slot];
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window->window);

    mouse->comp_position.position = sfRenderWindow_mapPixelToCoords(window->window, mouse_pos, window->cam.view);
    //play_animation(mouse, ANIM_MOUSE, true);
}

void init_mouse(world_t *world, win_t *window)
{
    int free_slot = find_empty(world);
    entity_t *mouse = &world->entity[free_slot];
    sfTexture *texture = sfTexture_createFromFile("effect/mouse.png", NULL);
    sfVector2f mouse_pos_f = (sfVector2f){sfMouse_getPositionRenderWindow(window->window).x, sfMouse_getPositionRenderWindow(window->window).x};

    init_comp_render(mouse, world, ANIM_MOUSE, mouse_pos_f);
    init_comp_hitbox(mouse, mouse_pos_f);
    init_comp_position(mouse, mouse_pos_f, world->map_id);
    mouse->comp_render.is_visible = true;
    mouse->comp_position.can_move = true;
    mouse->comp_hitbox.do_collide = false;
    mouse->mask |= COMP_MOUSE;
}