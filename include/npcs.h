/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** npcs
*/

#ifndef NPCS_H_
    #define NPCS_H_

    #include "world.h"
    #include "dialogs.h"

int set_npc_pos(world_t *world, entity_t *entity, char *args);
int set_world_id(world_t *world, entity_t *entity, char *args);
int set_idle(world_t *world, entity_t *entity, char *args);
int set_color(world_t *world, entity_t *entity, char *args);
int set_box(world_t *world, entity_t *entity, char *args);
int set_is_displayed(world_t *world, entity_t *entity, char *args);
int set_font(world_t *world, entity_t *entity, char *args);
int set_player_movement(world_t *world, entity_t *entity, char *args);
int set_loop(world_t *world, entity_t *entity, char *args);
int set_box_scale(world_t *world, entity_t *entity, char *args);
int set_input(world_t *world, entity_t *entity, char *args);
int set_camera_focus(world_t *world, entity_t *entity, char *args);
int gives_item(world_t *world, entity_t *entity, char *args);
int gives_item_dialog_id(world_t *world, entity_t *entity, char *args);
int gives_item_sentence_id(world_t *world, entity_t *entity, char *args);
int set_key_item_to_talk(world_t *world, entity_t *entity, char *args);
int set_key_item_to_drop(world_t *world, entity_t *entity, char *args);
int set_takes_item(world_t *world, entity_t *entity, char *args);
int takes_item_dialog_id(world_t *world, entity_t *entity, char *args);
int takes_item_sentence_id(world_t *world, entity_t *entity, char *args);
typedef struct ptr_funcs {
    char *name;
    int (*ptr)(world_t *world, entity_t *entity, char *args);
} ptr_func_t;

static const ptr_func_t NPC_ARGS[] = {
    {"dialog", &read_dialogs},
    {"pos", &set_npc_pos},
    {"world_id", &set_world_id},
    {"idle", &set_idle},
    {"talking", &set_idle},
    {"txt_color", &set_color},
    {"dialog_box", &set_box},
    {"is_displayed", &set_is_displayed},
    {"font", &set_font},
    {"freeze_player", &set_player_movement},
    {"loop", &set_loop},
    {"box_scale", &set_box_scale},
    {"need_input", &set_input},
    {"camera_focus", &set_camera_focus},
    {"gives_item", &gives_item},
    {"gives_item_dialog_id", &gives_item_dialog_id},
    {"gives_item_sentence_id", &gives_item_sentence_id},
    {"key_item_to_talk", &set_key_item_to_talk},
    {"key_item_to_drop", &set_key_item_to_drop},
    {"takes_item", &set_takes_item},
    {"takes_item_dialog_id", &takes_item_dialog_id},
    {"takes_item_sentence_id", &takes_item_sentence_id},
    {NULL, NULL}
};

void npc_collision(win_t *window, world_t *world, entity_t *entity);

#endif /* !NPCS_H_ */
