#ifndef BUTTONS_H
#define BUTTONS_H

#include "config.h"

typedef enum {
    BUTTON_MODE_TOGGLE,
    BUTTON_MANUAL_WATER,
} button_id_t;

void buttons_init(void);
bool button_is_pressed(button_id_t button);
bool button_was_pressed(button_id_t button);
void buttons_update(void);
void buttons_simulate_press(button_id_t button);

#endif // BUTTONS_H