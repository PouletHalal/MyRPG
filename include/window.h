/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** window
*/

#ifndef WINDOW_H_
    #define WINDOW_H_

    #include <SFML/Graphics/View.h>
    #include <SFML/Window/VideoMode.h>
    #include <SFML/Window/Event.h>
    #include <stdbool.h>

typedef struct cam_s {
    sfFloatRect view_rect;
    sfView *view;
    bool is_moving;
    sfVector2f *destination;
    sfVector2f offset;
} cam_t;

typedef struct window_s {
    sfVideoMode mode;
    sfRenderWindow *window;
    sfEvent event;
    sfVector2f windows_scale;
    cam_t cam;
    bool fullscreen;
    sfUint32 style;
    int sound;
    int music;
} win_t;


#endif /* !WINDOW_H_ */
