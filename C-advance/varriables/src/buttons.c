#include "../inc/buttons.h"

static button_state_t button_states[2] = {BUTTON_RELEASED, BUTTON_RELEASED};
static button_state_t prev_button_states[2] = {BUTTON_RELEASED, BUTTON_RELEASED};
static time_t last_button_time[2] = {0, 0};
static bool buttons_initialized = false;

void buttons_init(void) {
    printf("[BUTTONS] Initializing buttons...\n");
    
    for (int i = 0; i < 2; i++) {
        button_states[i] = BUTTON_RELEASED;
        prev_button_states[i] = BUTTON_RELEASED;
        last_button_time[i] = 0;
    }

    buttons_initialized = true;
    printf("[BUTTONS] Buttons initialized successfully\n");
}

bool button_is_pressed(button_id_t button) {
    if (!buttons_initialized || button > BUTTON_MANUAL_WATER) {
        return false;
    }

    return button_states[button] == BUTTON_PRESSED;
}

bool button_was_pressed(button_id_t button) {
    if (!buttons_initialized || button > BUTTON_MANUAL_WATER) {
        return false;
    }

    // Edge detection: button was released and now is pressed
    return (prev_button_states[button] == BUTTON_RELEASED && button_states[button] == BUTTON_PRESSED);
}

void buttons_update(void) {
    if (!buttons_initialized) {
        return;
    }

    // Store previous states
    for (int i = 0; i < 2; i++) {
        prev_button_states[i] = button_states[i];
    }
}

void buttons_simulate_press(button_id_t button) {
    if (!buttons_initialized || button > BUTTON_MANUAL_WATER) {
        return;
    }

    time_t current_time = time(NULL);

    // Simple debouncing simulation
    if (current_time - last_button_time[button] > 1) {
        prev_button_states[button] = button_states[button];
        button_states[button] = BUTTON_PRESSED;
        last_button_time[button] = current_time;
        printf("[BUTTONS] Button %d pressed\n", button);
    }
}