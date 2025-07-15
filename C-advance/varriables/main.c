#include <stdlib.h>
#include <unistd.h>
#include "inc/app.h"
#include "inc/buttons.h"
#include "inc/actuators.h"
#include "inc/sensors.h"
#include "inc/watering_logic.h"

system_config_t g_config;
system_state_t g_state;
sensor_data_t g_sensor_data;

int main(void) {
    printf("=== Smart Plant Watering System (SPWS) ===\n");
    printf("Initializing system...\n\n");

    srand(time(NULL));

    system_init();

    printf("\nSystem ready! Starting main loop...\n");
    printf("Press Ctrl+C to exit\n\n");

    int loop_count = 0;
    while (1) {
        simulate_system();

        if (loop_count % 10 == 0) {
            send_status_report();
        }

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

        sleep(1);

        if (loop_count > 30) {
            break;
        }
    }

    printf("\nSystem shutdown complete.\n");
    return 0;
}