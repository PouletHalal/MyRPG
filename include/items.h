/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** items
*/

#ifndef ITEMS_H_
    #define ITEMS_H_

    #include <SFML/Graphics/Font.h>
    #include "maps.h"
    #include "ecs.h"


typedef struct tooltip_s {
    char *name;
    char *description;
    sprite_t sprite;
    sfFont *font;
    sfText *name_txt;
    sfText *description_txt;
} tooltip_t;

typedef struct comp_item_s {
    int id_in_world;
    int id;
    int animation_id;
    int equip_mask;
    int type_mask;
    int quantity;
    double drop_rate;
    tooltip_t tooltip;
    comp_stat_t stats;
} comp_item_t;



#endif /* !ITEMS_H_ */
