/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** inventory
*/

#ifndef INVENTORY_H_
    #define INVENTORY_H_

    #include <stdbool.h>
    #include "items.h"



enum EQUIPEMENTS {
    EQUIP_NONE = 0,
    HELMET = 1 << 0,
    CHESTPLATE = 1 << 1,
    LEGGINGS = 1 << 2,
    BOOTS = 1 << 3,
    WEAPON = 1 << 4,
    SHIELD = 1 << 5,
    RING = 1 << 6,
    AMULET = 1 << 7,
};

enum ITEM_TYPES {
    ITEM_NONE = 0,
    ITEM_CONSUMABLE = 1 << 0,
    ITEM_EQUIPABLE = 1 << 1,
    ITEM_QUEST = 1 << 2,
    ITEM_KEY = 1 << 3,
    ITEM_LOOTABLE = 1 << 4,
    ITEM_STACKABLE = 1 << 5,
    ITEM_USABLE = 1 << 6,
};

typedef struct enum_names_s {
    int mask;
    char *name;
} enum_names_t;

static const enum_names_t EQUIP_NAMES[] = {
    {HELMET, "Helmet"},
    {CHESTPLATE, "Chestplate"},
    {LEGGINGS, "Leggings"},
    {BOOTS, "Boots"},
    {WEAPON, "Weapon"},
    {SHIELD, "Shield"},
    {RING, "Ring"},
    {AMULET, "Amulet"},
    {0, NULL}
};

static const enum_names_t ITEM_TYPES_NAMES[] = {
    {ITEM_CONSUMABLE, "consumable"},
    {ITEM_EQUIPABLE, "equipable"},
    {ITEM_QUEST, "quest"},
    {ITEM_KEY, "key"},
    {ITEM_LOOTABLE, "lootable"},
    {ITEM_STACKABLE, "stackable"},
    {ITEM_USABLE, "usable"},
    {0, NULL}
};

static const sfVector2i inv_coords[28] = {
    {84, 8}, {103, 8}, {122, 8}, {141, 8}, {160, 8}, {179, 8},
    {84, 27}, {103, 27}, {122, 27}, {141, 27}, {160, 27}, {179, 27},
    {84, 46}, {103, 46}, {122, 46}, {141, 46}, {160, 46}, {179, 46},
    {8, 74}, {27, 74}, {46, 74}, {65, 74}, {84, 74}, {103, 74}, {122, 74}, {141, 74}, {160, 74}, {179, 74}
};

typedef struct item_list_s {
    int nb_items;
    comp_item_t *items;
} item_list_t;

typedef struct comp_inventory_s {
    int size;
    bool is_open;
    comp_item_t *items;
    sprite_t sprite;
} comp_inventory_t;

#endif /* !INVENTORY_H_ */
