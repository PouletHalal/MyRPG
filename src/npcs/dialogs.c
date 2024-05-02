/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** dialogs
*/

#include <stdlib.h>
#include "temp.h"
#include "maps.h"
#include "player.h"
#include "rendering.h"
#include "camera.h"
#include "dialogs.h"

static void display_box(win_t *window, entity_t *entity)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(entity->comp_dialog.box);

    sfSprite_setOrigin(entity->comp_dialog.box,
    (sfVector2f) {bounds.width / 2, bounds.height / 2});
    sfSprite_setPosition(entity->comp_dialog.box, DIALOG_BOX_POS);
    sfRenderWindow_drawSprite(window->window, entity->comp_dialog.box, NULL);
}

static void display_txt(win_t *window, entity_t *entity)
{
    int dialog = entity->comp_dialog.current_dialog;
    int sentence = entity->comp_dialog.current_sentence;
    sfFloatRect bounds = {0};

    sfText_setString(entity->comp_dialog.sftext,
    entity->comp_dialog.text[dialog][sentence]);
    sfText_setCharacterSize(entity->comp_dialog.sftext, 40);
    bounds = sfText_getGlobalBounds(entity->comp_dialog.sftext);
    sfText_setOrigin(entity->comp_dialog.sftext, (sfVector2f)
    {bounds.width / 2, bounds.height / 2});
    sfText_setPosition(entity->comp_dialog.sftext, DIALOG_BOX_POS);
    sfText_setColor(entity->comp_dialog.sftext, entity->comp_dialog.color);
    sfRenderWindow_drawText(window->window, entity->comp_dialog.sftext, NULL);
}

static void disable_far_dialogs(world_t *world, entity_t *entity)
{
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];
    sfVector2f pos1 = player->comp_position.position;
    sfVector2f pos2 = entity->comp_position.position;

    if (abs(pos1.x - pos2.x) >= 60 || abs(pos1.y - pos2.y) >= 60)
        entity->comp_dialog.is_displayed = false;
}

void display_dialogs(win_t *window, world_t *world)
{
    sfRenderWindow_setView(window->window,
    sfRenderWindow_getDefaultView(window->window));
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        if ((world->entity[i].mask & COMP_DIALOG) == COMP_DIALOG &&
            world->entity[i].comp_dialog.is_displayed == true) {
            display_box(window, &world->entity[i]);
            display_txt(window, &world->entity[i]);
            disable_far_dialogs(world, &world->entity[i]);
        }
    }
    sfRenderWindow_display(window->window);
    sfRenderWindow_setView(window->window, window->cam.view);
}

static void update_dialog(entity_t *entity)
{
    int dialog = entity->comp_dialog.current_dialog;
    int sentence = entity->comp_dialog.current_sentence;

    if (dialog == -1) {
        entity->comp_dialog.current_dialog = 0;
        return;
    }
    if (sentence == -1) {
        entity->comp_dialog.current_sentence = 0;
        return;
    }
    mini_update_dialog(sentence, entity, dialog);
}

void mini_update_dialog(int sentence, entity_t *entity, int dialog)
{
    if (sentence + 1 == len_array(entity->comp_dialog.text[dialog])) {
        entity->comp_dialog.current_sentence = -1;
        entity->comp_dialog.current_dialog += 1;
        entity->comp_dialog.is_displayed = false;
    } else
        entity->comp_dialog.current_sentence += 1;
    if (entity->comp_dialog.current_dialog >= entity->comp_dialog.nb_dialogs) {
        entity->comp_dialog.is_displayed = false;
        entity->comp_dialog.current_dialog = -1;
        entity->comp_dialog.current_sentence = 0;
    }
}

static bool start_dialog(win_t *window, world_t *world, entity_t *entity,
    sfVector2f velocity)
{
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        if (entity->entity != i &&
        ((world->entity[i].mask & COMP_DIALOG) == COMP_DIALOG) &&
        world->key_pressed[sfKeySpace] == true &&
        collide_entity(entity, &world->entity[i], velocity) == true) {
            world->entity[i].comp_dialog.is_displayed = true;
            world->entity[i].comp_position.can_move = false;
            update_dialog(&world->entity[i]);
            return true;
        }
    }
    return false;
}

bool temp(win_t *window, world_t *world, entity_t *entity, float x)
{
    for (float y = -THRESHOLD; y <= THRESHOLD; ++y)
        if (start_dialog(window, world, entity, (sfVector2f) {x, y}))
            return true;
    return false;
}
