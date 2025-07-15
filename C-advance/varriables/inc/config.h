#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define DEFAULT_MIN_MOISTURE              30
#define DEFAULT_MAX_MOISTURE              70
#define DEFAULT_MAX_WATERING_TIME         60
#define DEFAULT_SENSOR_CHECK_INTERVAL     300  // 5 minutes
#define DEFAULT_MIN_WAIT_BETWEEN_WATERING 1800 // 30 minutes
#define MANUAL_WATERING_TIME              10   // 10 seconds for manual watering
#define BUTTON_DEBOUNCE_MS                50

typedef enum {
    MODE_AUTO,
    MODE_MANUAL,
} system_mode_t;

typedef enum {
    PUMP_OFF,
    PUMP_ON,
} pump_state_t;

typedef enum {
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR,
} led_state_t;

typedef enum {
    BUTTON_RELEASED,
    BUTTON_PRESSED,
} button_state_t;

typedef struct {
    uint8_t soil_moisture_percent;
    int16_t temperature_celsius;
    time_t last_reading_time;
} sensor_data_t;

typedef struct {
    uint8_t min_moisture_threshold;
    uint8_t max_moisture_threshold;
    uint16_t max_watering_time_sec;
    uint16_t sensor_check_interval_sec;
    uint16_t min_wait_between_watering_sec;
    system_mode_t current_mode;
} system_config_t;

typedef struct {
    pump_state_t pump_state;
    led_state_t led_state;
    time_t watering_start_time;
    time_t last_watering_time;
    time_t last_sensor_check;
    bool system_error;
} system_state_t;

#endif // CONFIG_H