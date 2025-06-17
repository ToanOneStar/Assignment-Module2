#include "../inc/watering_logic.h"
#include "../inc/actuators.h"

void watering_logic_init(system_config_t* config, system_state_t* state) {
    printf("[LOGIC] Initializing watering logic...\n");

    // Initialize default configuration
    config->min_moisture_threshold = DEFAULT_MIN_MOISTURE;
    config->max_moisture_threshold = DEFAULT_MAX_MOISTURE;
    config->max_watering_time_sec = DEFAULT_MAX_WATERING_TIME;
    config->sensor_check_interval_sec = DEFAULT_SENSOR_CHECK_INTERVAL;
    config->min_wait_between_watering_sec = DEFAULT_MIN_WAIT_BETWEEN_WATERING;
    config->current_mode = MODE_AUTO;

    // Initialize system state
    state->pump_state = PUMP_OFF;
    state->led_state = LED_NORMAL;
    state->watering_start_time = 0;
    state->last_watering_time = 0;
    state->last_sensor_check = 0;
    state->system_error = false;

    printf("[LOGIC] Watering logic initialized - Mode: AUTO\n");
}

void watering_logic_process(system_config_t* config, system_state_t* state, sensor_data_t* sensor_data) {
    time_t current_time = time(NULL);

    // Only process automatic watering in AUTO mode
    if (config->current_mode != MODE_AUTO) {
        return;
    }

    // Check if it's time to read sensors
    if (current_time - state->last_sensor_check >= config->sensor_check_interval_sec) {
        state->last_sensor_check = current_time;
        if (state->pump_state == PUMP_OFF) {
            if (should_start_watering(config, state, sensor_data)) {
                pump_turn_on();
                state->pump_state = PUMP_ON;
                state->watering_start_time = current_time;
                printf("[LOGIC] Auto watering started - Moisture: %d%%\n", sensor_data->soil_moisture_percent);
            }
        } else {
            if (should_stop_watering(config, state, sensor_data)) {
                pump_turn_off();
                state->pump_state = PUMP_OFF;
                state->last_watering_time = current_time;
                printf("[LOGIC] Auto watering stopped - Moisture: %d%%\n", sensor_data->soil_moisture_percent);
            }
        }
    }

    update_led_status(config, state, sensor_data);
}

bool should_start_watering(const system_config_t* config, const system_state_t* state,
                           const sensor_data_t* sensor_data) {
    time_t current_time = time(NULL);

    // Check if moisture is below threshold
    if (sensor_data->soil_moisture_percent >= config->min_moisture_threshold) {
        return false;
    }

    // Check if enough time has passed since last watering
    if (current_time - state->last_watering_time < config->min_wait_between_watering_sec) {
        return false;
    }

    // Check for system error
    if (state->system_error) {
        return false;
    }

    return true;
}

bool should_stop_watering(const system_config_t* config, const system_state_t* state,
                          const sensor_data_t* sensor_data) {
    time_t current_time = time(NULL);

    // Stop if moisture threshold is reached
    if (sensor_data->soil_moisture_percent >= config->max_moisture_threshold) {
        return true;
    }

    // Stop if maximum watering time is reached
    if (current_time - state->watering_start_time >= config->max_watering_time_sec) {
        return true;
    }

    // Stop if system error occurs
    if (state->system_error) {
        return true;
    }

    return false;
}

void start_manual_watering(system_state_t* state) {
    if (state->pump_state == PUMP_OFF) {
        pump_turn_on();
        state->pump_state = PUMP_ON;
        state->watering_start_time = time(NULL);
        printf("[LOGIC] Manual watering started\n");
    }
}

void update_led_status(system_config_t* config, system_state_t* state, sensor_data_t* sensor_data) {
    led_state_t new_led_state;

    if (state->system_error) {
        new_led_state = LED_ERROR;
    } else if (state->pump_state == PUMP_ON) {
        new_led_state = LED_WATERING;
    } else if (sensor_data->soil_moisture_percent < config->min_moisture_threshold) {
        new_led_state = LED_LOW_MOISTURE_ALERT;
    } else {
        new_led_state = LED_NORMAL;
    }

    if (state->led_state != new_led_state) {
        state->led_state = new_led_state;
        led_set_state(new_led_state);
    }
}