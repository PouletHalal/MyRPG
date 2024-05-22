/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** world
*/

#ifndef WORLD_H_
    #define WORLD_H_

    #include "maps.h"
    #include "sounds.h"
    #include "ecs.h"
    #include "inventory.h"
    #include "items.h"
    #include "window.h"

    #define RENDER_DISTANCE 600. * 600.
    #define DISPAWN_RANGE 800. * 800.

typedef struct entity_s {
    int mask;
    int entity;
    comp_render_t comp_render;
    comp_position_t comp_position;
    comp_input_t comp_input;
    comp_mob_t comp_mob;
    comp_hitbox_t comp_hitbox;
    comp_portal_t comp_portal;
    comp_dialog_t comp_dialog;
    comp_input_t comp_ui;
    comp_stat_t comp_stat;
    comp_inventory_t comp_inventory;
    comp_item_t comp_item;
    comp_hud_t comp_hud;
} entity_t;

typedef struct world_s {
    enum map_ids map_id;
    map_list_t **map_list;
    sound_list_t **sound_list;
    sfTexture **texture_list;
    entity_t entity[ENTITY_COUNT];
    item_list_t item_list;
    animation_t *animations;
    sfBool key_pressed[NB_KEYS];
    sfBool key_down[NB_KEYS];
    sfBool mouse_left_pressed;
    sfBool mouse_right_pressed;
} world_t;

void init_entity(world_t *world, animation_t *anim, sfVector2f position);
void init_mob(world_t *world, animation_t *anim, sfVector2f position);
void init_comp_portal(entity_t *entity, char **split);
void init_comp_render(entity_t *entity, world_t *world,
    animation_t *anim, sfVector2f position);
void init_comp_hitbox(entity_t *entity, sfVector2f position);
void init_comp_mob(entity_t *entity);
void init_comp_input(entity_t *entity, world_t *world);
void init_comp_position(entity_t *entity, sfVector2f position, int world_id);

void sys_stat(win_t *window, world_t *world);
void sys_mob(world_t *world, win_t *win);
void sys_render(world_t *world);

void refresh_sounds(world_t *world, sfClock *clock);
bool is_close(entity_t *entity, entity_t *bis, sfVector2f threshold);

int init_inventory(world_t *world, entity_t *entity, int size);
bool add_item_to_inv(entity_t *entity, entity_t *item, int i);
bool item_collision(world_t *world, entity_t *entity);
int read_items_conf(world_t *world);
void read_animconf(world_t *world);
int get_anim_id(world_t *world, char *name);
void create_item(world_t *world, sfVector2f pos);

#endif /* !WORLD_H_ */
