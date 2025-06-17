#include <stdlib.h>
#include <unistd.h>
#include "inc/actuators.h"
#include "inc/buttons.h"
#include "inc/config.h"
#include "inc/sensors.h"
#include "inc/watering_logic.h"

// Global system variables
static system_config_t g_config;
static system_state_t g_state;
static sensor_data_t g_sensor_data;

void system_init(void);
void process_buttons(void);
void send_status_report(void);
void simulate_user_input(void);

int main(void) {
    printf("=== Smart Plant Watering System (SPWS) ===\n");
    printf("Initializing system...\n\n");

    // Initialize random seed for sensor simulation
    srand(time(NULL));

    // Initialize all system components
    system_init();

    printf("\nSystem ready! Starting main loop...\n");
    printf("Press Ctrl+C to exit\n\n");

    int loop_count = 0;
    while (1) {
        if (!sensors_read_data(&g_sensor_data)) {
            printf("[ERROR] Failed to read sensor data\n");
            g_state.system_error = true;
        } else {
            g_state.system_error = false;
        }

        process_buttons();
        watering_logic_process(&g_config, &g_state, &g_sensor_data);

        // Handle manual watering timeout
        if (g_config.current_mode == MODE_MANUAL && g_state.pump_state == PUMP_ON) {
            time_t current_time = time(NULL);
            if (current_time - g_state.watering_start_time >= MANUAL_WATERING_TIME) {
                pump_turn_off();
                g_state.pump_state = PUMP_OFF;
                printf("[LOGIC] Manual watering timeout - stopped\n");
            }
        }

        if (loop_count % 10 == 0) {
            send_status_report();
        }

        // Simulate some user button presses for demonstration
        switch (loop_count) {
            case 5:
                printf("\n[DEMO] Simulating mode toggle button press...\n");
                buttons_simulate_press(BUTTON_MODE_TOGGLE);
                break;
            case 15:
                printf("\n[DEMO] Simulating manual watering button press...\n");
                buttons_simulate_press(BUTTON_MANUAL_WATER);
                break;
            case 25:
                printf("\n[DEMO] Simulating mode toggle back to AUTO...\n");
                buttons_simulate_press(BUTTON_MODE_TOGGLE);
                break;
            default: break;
        }

        buttons_update();
        loop_count++;

        // Delay to simulate real-time operation (1 second intervals)
        sleep(1);

        // Exit after demonstration
        if (loop_count > 30) {
            break;
        }
    }

    printf("\nSystem shutdown complete.\n");

    return 0;
}

void system_init(void) {
    // Initialize all system modules
    sensors_init();
    actuators_init();
    buttons_init();
    watering_logic_init(&g_config, &g_state);

    // Initial sensor reading
    if (!sensors_read_data(&g_sensor_data)) {
        printf("[ERROR] Initial sensor reading failed\n");
        g_state.system_error = true;
    }

    printf("[SYSTEM] Initialization complete\n");
}

void process_buttons(void) {
    // Check mode toggle button
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

    // Check manual watering button (only works in manual mode)
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