#include <stdlib.h>
#include <string.h>
#include "led_driver.h"

#define SHIFT_BIT_LED_GREEN 16
#define SHIFT_BIT_LED_RED   8
#define SHIFT_BIT_LED_BLUE  0

static uint32_t* led_buffer = NULL;
static size_t pixel_count = 0;

int led_init(size_t num_pixels) {
    if (led_buffer != NULL) {
        led_shutdown();
    }

    if (num_pixels == 0) {
        return -1;
    }

    led_buffer = (uint32_t*)calloc(num_pixels, sizeof(uint32_t));
    if (led_buffer == NULL) {
        return -1; // memory allocation failed
    }

    pixel_count = num_pixels;
    return 0;
}

void led_shutdown() {
    if (led_buffer != NULL) {
        free(led_buffer);
        led_buffer = NULL;
    }
    pixel_count = 0;
}

void led_set_pixel_color(size_t index, uint8_t red, uint8_t green, uint8_t blue) {
    if (led_buffer == NULL || index >= pixel_count || index < 0) {
        return;
    }

    uint32_t color = ((uint32_t)green << SHIFT_BIT_LED_GREEN
                      | ((uint32_t)red << SHIFT_BIT_LED_RED | (uint32_t)blue << SHIFT_BIT_LED_BLUE));
    led_buffer[index] = color;
}

void led_fill(uint8_t red, uint8_t green, uint8_t blue) {
    if (led_buffer == NULL) {
        return;
    }

    uint32_t color = ((uint32_t)green << SHIFT_BIT_LED_GREEN
                      | ((uint32_t)red << SHIFT_BIT_LED_RED | (uint32_t)blue << SHIFT_BIT_LED_BLUE));

    for (size_t i = 0; i < pixel_count; ++i) {
        led_buffer[i] = color;
    }
}

void led_clear() {
    led_fill(0, 0, 0);
}

const uint32_t* led_get_buffer() {
    return (const uint32_t*)led_buffer;
}

size_t led_get_pixel_count() {
    return pixel_count;
}
