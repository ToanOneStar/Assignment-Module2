#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

int led_init(size_t num_pixels);
void led_shutdown();
void led_set_pixel_color(size_t index, uint8_t red, uint8_t green, uint8_t blue);
void led_fill(uint8_t red, uint8_t green, uint8_t blue);
void led_clear();
const uint32_t* led_get_buffer();
size_t led_get_pixel_count();

#endif // LED_DRIVER_H