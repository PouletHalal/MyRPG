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
    #define WEATHER_RATE 0.01

typedef struct comp_ui_s {
    int ui_mask;
    int next_mask;
    char *name;
    sfText *text;
    sfFont *font;
    animation_t *hover;
    animation_t *base;
    char *func_name;
} comp_ui_t;

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
    comp_stat_t comp_stat;
    comp_inventory_t comp_inventory;
    comp_item_t comp_item;
    comp_mouse_t comp_mouse;
    comp_hud_t comp_hud;
    comp_npc_t comp_npc;
    comp_spell_t comp_spell;
    comp_particle_t comp_particle;
    comp_ui_t comp_ui;
} entity_t;

enum weather {
    CLEAR,
    RAIN,
    MAX_WEATHER,
};

typedef struct world_s {
    bool is_paused;
    int ui_id;
    enum map_ids map_id;
    map_list_t **map_list;
    sound_list_t **sound_list;
    sfTexture **texture_list;
    item_list_t item_list;
    effect_t *effect_list;
    animation_t *animations;
    comp_spell_t *spell_list;
    entity_t entity[ENTITY_COUNT];
    sfBool key_pressed[NB_KEYS];
    sfBool key_down[NB_KEYS];
    sfBool mouse_left_pressed;
    sfBool mouse_right_pressed;
    enum weather weather;
    sfSprite *light_sprite;
    int sound_volume;
    int music_volume;
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
void sys_render(win_t *window, world_t *world);

void refresh_sounds(world_t *world, sfClock *clock);
bool is_close(entity_t *entity, entity_t *bis, sfVector2f threshold);

int init_inventory(world_t *world, entity_t *entity, int size);
bool add_item_to_inv(entity_t *entity, entity_t *item, int i);
bool item_collision(world_t *world, entity_t *entity);
int read_items_conf(world_t *world);
void create_item(world_t *world, sfVector2f pos, int item_id);
sfVector2f get_pos_from_slot(entity_t *entity, int slot);
int get_slot_from_pos(entity_t *entity, sfVector2i mouse_pos);
bool drop_item(world_t *world, entity_t *item, sfVector2i mouse_pos, int i);
bool is_mouse_over(sfVector2i pos, entity_t *entity);
void read_animconf(world_t *world);
int get_anim_id(world_t *world, char *name);
int get_item_id(item_list_t items, char const *name);
sfBool is_in_inv(world_t *world, entity_t *entity, int id);
int find_item_in_inv(entity_t *entity, int id);
void add_effect(world_t *world, entity_t *entity, enum effect effect_index);
void respawn_entity(win_t *window, entity_t *entity);
void follow_enemy(entity_t *spell, entity_t *enemy);
entity_t *get_closest(entity_t *entity, world_t *world);
void create_spell(world_t *world, entity_t *player,
    sfVector2f position, int spell_id);
void sys_spell(world_t *world);
void loop_effect(entity_t *entity);
int set_spell_anim(world_t *world, comp_spell_t *spell, char *args);
int set_spell_target(world_t *world, comp_spell_t *spell, char *args);
int read_effect_conf(world_t *world);
int read_spells_conf(world_t *world);
void manage_inv_slots(world_t *world, win_t *window, entity_t *entity);
void drag_item_inv(entity_t *entity, entity_t *mouse, int slot);
void put_back_item_if_inv_closed(world_t *world, entity_t *player);
void read_ui_conf(world_t *world);
sfSprite *create_light(int size, sfColor color);

#endif /* !WORLD_H_ */
