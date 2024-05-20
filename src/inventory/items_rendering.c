/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** item_rendeing
*/

#include "temp.h"


static void display_text(win_t *win, sfText *text, sfVector2f pos)
{
    sfText_setPosition(text, pos);
    sfRenderWindow_drawText(win->window, text, NULL);
}

void display_tooltips(win_t *window, entity_t *item, sfVector2f pos)
{
    item->comp_item.tooltip.sprite.pos = pos;

    if (item->comp_item.tooltip.sprite.sprite == NULL)
        return;
    sfSprite_setPosition(item->comp_item.tooltip.sprite.sprite, pos);
    sfSprite_setScale(item->comp_item.tooltip.sprite.sprite,
    item->comp_item.tooltip.sprite.scale);
    sfRenderWindow_drawSprite(window->window,
    item->comp_item.tooltip.sprite.sprite, NULL);
    display_text(window, item->comp_item.tooltip.name_txt,
    (sfVector2f) {pos.x + 10, pos.y + 20});
    display_text(window, item->comp_item.tooltip.description_txt,
    (sfVector2f) {pos.x + 10, pos.y + 50});
}
