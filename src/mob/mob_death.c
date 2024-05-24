/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** mob_death
*/

#include <stdlib.h>
#include "temp.h"
#include "player.h"

void mob_death(world_t *world, entity_t *entity)
{
    int player_id = find_comp(world, COMP_PLAYER);
    entity_t *player = NULL;
    int rand_item = 0;

    if ((entity->mask & COMP_MOB) != COMP_MOB || player_id == -1)
        return;
    player = &world->entity[player_id];
    player->comp_stat.exp += entity->comp_stat.exp_loot;
    if (world->item_list.nb_items == 0)
        return;
    if (rand() % 10 == 0) {
        for (rand_item = rand() % world->item_list.nb_items;
        (world->item_list.items[rand_item].type_mask & ITEM_LOOTABLE) !=
        ITEM_LOOTABLE; rand_item = rand() % world->item_list.nb_items);
        create_item(world, entity->comp_position.position,
        rand_item);
    }
}
