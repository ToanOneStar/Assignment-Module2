#include "../inc/actuators.h"

static pump_state_t current_pump_state = PUMP_OFF;
static led_state_t current_led_state = LED_NORMAL;
static bool actuators_initialized = false;

void actuators_init(void) {
    printf("[ACTUATORS] Initializing actuators...\n");
    
    current_pump_state = PUMP_OFF;
    current_led_state = LED_NORMAL;
    actuators_initialized = true;

    printf("[ACTUATORS] Pump: OFF, LED: NORMAL\n");
    printf("[ACTUATORS] Actuators initialized successfully\n");
}

void pump_turn_on(void) {
    if (!actuators_initialized) {
        return;
    }

    current_pump_state = PUMP_ON;
    printf("[PUMP] Pump turned ON - Watering started\n");
}

void pump_turn_off(void) {
    if (!actuators_initialized) {
        return;
    }

    current_pump_state = PUMP_OFF;
    printf("[PUMP] Pump turned OFF - Watering stopped\n");
}

pump_state_t pump_get_state(void) {
    return current_pump_state;
}

void led_set_state(led_state_t state) {
    if (!actuators_initialized) {
        return;
    }

    current_led_state = state;
    switch (state) {
        case LED_NORMAL: 
            printf("[LED] Status: GREEN - System normal\n"); 
            break;
        case LED_WATERING: 
            printf("[LED] Status: YELLOW - Watering in progress\n"); 
            break;
        case LED_LOW_MOISTURE_ALERT: 
            printf("[LED] Status: ORANGE - Low moisture alert\n"); 
            break;
        case LED_ERROR: 
            printf("[LED] Status: RED - System error\n"); 
            break;
    }
}

led_state_t led_get_state(void) {
    return current_led_state;
}

void actuators_update_status(void) {
    printf("[ACTUATORS] Pump: %s, LED: %d\n", (current_pump_state == PUMP_ON) ? "ON" : "OFF", current_led_state);
}