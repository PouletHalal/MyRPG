/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** sys_ui
*/

#include "ui.h"
#include "world.h"
#include "rendering.h"

static void update_texture_rect(comp_render_t *c_render)
{
    animation_t *anim = c_render->current_animation;
    sfVector2u sheet_size = sfTexture_getSize(c_render->texture);
    int frame_per_line = sheet_size.x / anim->frame_size.x;
    sfIntRect rect = {0};

    rect.left = anim->base_text_rect.left + anim->frame_size.x *
    (c_render->act_frame % frame_per_line);
    rect.top = anim->base_text_rect.top + anim->frame_size.y *
    (c_render->act_frame / frame_per_line);
    rect.width = anim->frame_size.x;
    rect.height = anim->frame_size.y;
    sfSprite_setTextureRect(c_render->sprite, rect);
}

static void next_frame(entity_t *entity, world_t *world)
{
    comp_render_t *c_render = &entity->comp_render;
    animation_t *anim = c_render->current_animation;

    sfSprite_setPosition(c_render->sprite, entity->comp_position.position);
    if (c_render->clock < anim->frame_rate){
        c_render->clock += 1;
        return;
    }
    c_render->clock = 0;
    c_render->act_frame += 1;
    if (c_render->act_frame >= anim->frame_count)
        if (c_render->does_loop == false)
            return;
        else
            c_render->act_frame = 0;
    update_texture_rect(c_render);
}

static void ui_events(win_t *win, world_t *world, entity_t *button)
{
    if (is_mouse_over(sfMouse_getPositionRenderWindow(win->window), button)) {
        play_animation(world, button, button->comp_ui.hover->index, 1);
    } else {
        return play_animation(world, button, button->comp_ui.base->index, 1);
    }
    if (world->mouse_left_pressed == false)
        return;
    world->ui_id = button->comp_ui.next_mask;
}

void sys_ui(win_t *window, world_t *world)
{
    if (world->ui_id == UI_NONE)
        return;
    sfRenderWindow_setView(window->window,
    sfRenderWindow_getDefaultView(window->window));
    for (int i = 0; i < ENTITY_COUNT; i++) {
        if ((world->entity[i].mask & COMP_UI) == COMP_UI &&
            world->entity[i].comp_ui.ui_mask == world->ui_id) {
            ui_events(window, world, &world->entity[i]);
            next_frame(&world->entity[i], world);
            sfRenderWindow_drawSprite(window->window,
            world->entity[i].comp_render.sprite, NULL);
        }
    }
    sfRenderWindow_setView(window->window, window->cam.view);
    sfRenderWindow_display(window->window);
}
