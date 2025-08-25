#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "config.h"

void actuators_init(void);
void pump_turn_on(void);
void pump_turn_off(void);
pump_state_t pump_get_state(void);
void led_set_state(led_state_t state);
led_state_t led_get_state(void);
void actuators_update_status(void);

#endif // ACTUATORS_H