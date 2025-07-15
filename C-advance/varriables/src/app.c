#include "../inc/app.h"
#include "../inc/buttons.h"

void system_init(void) {
    sensors_init();
    actuators_init();
    buttons_init();
    watering_logic_init(&g_config, &g_state);

    if (!sensors_read_data(&g_sensor_data)) {
        printf("[ERROR] Initial sensor reading failed\n");
        g_state.system_error = true;
    }

    printf("[SYSTEM] Initialization complete\n");
}

void process_buttons(void) {
    if (button_was_pressed(BUTTON_MODE_TOGGLE)) {
        if (g_config.current_mode == MODE_AUTO) {
            g_config.current_mode = MODE_MANUAL;
            if (g_state.pump_state == PUMP_ON) {
                pump_turn_off();
                g_state.pump_state = PUMP_OFF;
            }
            printf("[SYSTEM] Mode changed to MANUAL\n");
        } else {
            g_config.current_mode = MODE_AUTO;
            printf("[SYSTEM] Mode changed to AUTO\n");
        }
    }

    if (button_was_pressed(BUTTON_MANUAL_WATER)) {
        if (g_config.current_mode == MODE_MANUAL && g_state.pump_state == PUMP_OFF) {
            start_manual_watering(&g_state);
        } else if (g_config.current_mode == MODE_AUTO) {
            printf("[BUTTONS] Manual watering ignored - system in AUTO mode\n");
        } else if (g_state.pump_state == PUMP_ON) {
            printf("[BUTTONS] Manual watering ignored - pump already running\n");
        }
    }
}

void send_status_report(void) {
    printf("\n--- STATUS REPORT ---\n");
    printf("Mode: %s\n", (g_config.current_mode == MODE_AUTO) ? "AUTO" : "MANUAL");
    printf("Soil Moisture: %d%% (Min: %d%%, Max: %d%%)\n",
           g_sensor_data.soil_moisture_percent,
           g_config.min_moisture_threshold,
           g_config.max_moisture_threshold);
    printf("Temperature: %d°C\n", g_sensor_data.temperature_celsius);
    printf("Pump: %s\n", (g_state.pump_state == PUMP_ON) ? "ON" : "OFF");

    const char* led_status[] = {"NORMAL", "WATERING", "LOW_MOISTURE", "ERROR"};
    printf("LED Status: %s\n", led_status[g_state.led_state]);

    if (g_state.system_error) {
        printf("System Status: ERROR\n");
    } else {
        printf("System Status: OK\n");
    }
    printf("--------------------\n\n");
}