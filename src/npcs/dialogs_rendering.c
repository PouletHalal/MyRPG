/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** dialog_rendering
*/

#include <stdlib.h>
#include "temp.h"
#include "player.h"
#include "dialogs.h"


static void disable_far_dialogs(world_t *world, entity_t *entity)
{
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];
    sfVector2f pos1 = player->comp_position.position;
    sfVector2f pos2 = entity->comp_position.position;

    if (entity->comp_dialog.freeze_player == true ||
        entity->comp_dialog.need_input == false)
        return;
    if (abs(pos1.x - pos2.x) >= 60 || abs(pos1.y - pos2.y) >= 60)
        entity->comp_dialog.is_displayed = false;
}

static void display_txt(win_t *window, entity_t *entity)
{
    int dialog = entity->comp_dialog.current_dialog;
    int sentence = entity->comp_dialog.current_sentence;
    sfFloatRect bounds = {0};

    update_substring(entity, dialog, sentence);
    sfText_setString(entity->comp_dialog.sftext,
    entity->comp_dialog.substring);
    sfText_setCharacterSize(entity->comp_dialog.sftext, 40);
    bounds = sfText_getGlobalBounds(entity->comp_dialog.sftext);
    sfText_setOrigin(entity->comp_dialog.sftext, (sfVector2f)
    {bounds.width / 2, bounds.height / 2});
    sfText_setPosition(entity->comp_dialog.sftext, DIALOG_BOX_POS);
    sfText_setColor(entity->comp_dialog.sftext, entity->comp_dialog.color);
    sfRenderWindow_drawText(window->window, entity->comp_dialog.sftext, NULL);
}

static void display_box(win_t *window, entity_t *entity)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(entity->comp_dialog.box);
    sfVector2f scale = sfSprite_getScale(entity->comp_dialog.box);

    sfSprite_setOrigin(entity->comp_dialog.box,
    (sfVector2f) {bounds.width / 2 / scale.x, bounds.height / 2 / scale.y});
    sfSprite_setPosition(entity->comp_dialog.box, DIALOG_BOX_POS);
    sfRenderWindow_drawSprite(window->window, entity->comp_dialog.box, NULL);
}

void display_dialogs(win_t *window, world_t *world)
{
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];

    sfRenderWindow_setView(window->window,
    sfRenderWindow_getDefaultView(window->window));
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        if ((world->entity[i].mask & COMP_PLAYER) == COMP_PLAYER)
            player = &world->entity[i];
        if ((world->entity[i].mask & COMP_DIALOG) == COMP_DIALOG &&
            world->entity[i].comp_dialog.is_displayed == true &&
            world->entity[i].comp_dialog.is_finished == false) {
            display_box(window, &world->entity[i]);
            display_txt(window, &world->entity[i]);
            disable_far_dialogs(world, &world->entity[i]);
        }
    }
    sfRenderWindow_display(window->window);
    sfRenderWindow_setView(window->window, window->cam.view);
}
