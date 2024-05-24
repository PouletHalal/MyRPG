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

    if ((entity->mask & COMP_MOB) != COMP_MOB || player_id == -1)
        return;
    player = &world->entity[player_id];
    player->comp_stat.exp += entity->comp_stat.exp_loot;
    if (rand() % 10 == 0)
        create_item(world, entity->comp_position.position,
        rand() % world->item_list.nb_items);
}
