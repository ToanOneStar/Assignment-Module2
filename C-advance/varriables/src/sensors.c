#include <stdlib.h>
#include "../inc/sensors.h"

static bool sensor_initialized = false;

void sensors_init(void) {
    printf("[SENSORS] Initializing sensors...\n");

    // Simulate GPIO and ADC initialization
    sensor_initialized = true;
    printf("[SENSORS] Sensors initialized successfully\n");
}

bool sensors_read_data(sensor_data_t* data) {
    if (!sensor_initialized || data == NULL) {
        return false;
    }

    data->soil_moisture_percent = rand() % 101;
    data->temperature_celsius = 15 + (rand() % 21);
    data->last_reading_time = time(NULL);

    printf("[SENSORS] Soil moisture: %d%%, Temperature: %d Degree C\n",
           data->soil_moisture_percent,
           data->temperature_celsius);

    return true;
}

uint8_t sensors_get_soil_moisture(void) {
    if (!sensor_initialized) {
        return 0;
    }

    return rand() % 101;
}

int16_t sensors_get_temperature(void) {
    if (!sensor_initialized) {
        return 0;
    }

    return 15 + (rand() % 21);
}

bool sensors_is_data_valid(const sensor_data_t* data) {
    if (data == NULL) {
        return false;
    }

    if (data->soil_moisture_percent > 100) {
        return false;
    }

    if (data->temperature_celsius < -40 || data->temperature_celsius > 80) {
        return false;
    }

    return true;
}