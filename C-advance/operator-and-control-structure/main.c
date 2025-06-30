#include <stdint.h>
#include <stdio.h>
#include "led_driver.h"

#define VALUE_LED_RED   0x0000FF00
#define VALUE_LED_BLUE  0x000000FF
#define VALUE_LED_WHITE 0x00FFFFFF
#define VALUE_LED_GREEN 0x00FF0000

void print_test_result(const char* test_name, int passed) {
    printf("[%s] %s\n", passed ? "PASS" : "FAIL", test_name);
}

int main() {
    printf("=== LED Driver Test Case ===\n\n");

    // test 1: initialize LED strip with 10 pixels
    printf("1. Initializing LED strip with 10 pixels...\n");
    int init_result = led_init(10);
    print_test_result("LED initialization", init_result == 0);

    if (init_result != 0) {
        printf("Fail to initialize LED strip. Exiting\n");
        return -1;
    }

    // test 2: check if buffer is initialized to 0
    printf("\n2. Checking if buffer is initialized to 0...\n");
    const uint32_t* buffer = led_get_buffer();
    int all_zero = 1;

    for (size_t i = 0; i < led_get_pixel_count(); ++i) {
        if (buffer[i] != 0) {
            all_zero = 0;
            break;
        }
    }
    print_test_result("Buffer initialized to 0", all_zero);

    // test 3: set pixel colors
    printf("\n3. Setting pixel colors...\n");
    led_set_pixel_color(0, 255, 0, 0);
    led_set_pixel_color(9, 0, 0, 255);
    led_set_pixel_color(4, 255, 255, 255);

    // test 4: verify pixel colors
    printf("\n4. Verifying pixel colors...\n");
    buffer = led_get_buffer();

    printf("Pixel 0 (Red): Value = 0x%08X\n", buffer[0]);
    print_test_result("Pixel 0 is Red", buffer[0] == VALUE_LED_RED);

    printf("Pixel 9 (Blue): Value = 0x%08X\n", buffer[9]);
    print_test_result("Pixel 9 is Blue", buffer[9] == VALUE_LED_BLUE);

    printf("Pixel 4 (White): Value = 0x%08X\n", buffer[4]);
    print_test_result("Pixel 4 is White", buffer[4] == VALUE_LED_WHITE);

    // test 5: fill with green
    printf("\n5. Filling entire strip with Green...\n");
    led_fill(0, 255, 0);

    // test 6: verify all pixels are green
    printf("\n6. Verifying all pixels are Green...\n");
    buffer = led_get_buffer();
    int all_green = 1;

    for (size_t i = 0; i < led_get_pixel_count(); ++i) {
        if (buffer[i] != VALUE_LED_GREEN) {
            all_green = 0;
        }
    }

    print_test_result("All pixels are Green", all_green);

    // test 7: cleanup
    printf("\n10. Cleaning up...\n");
    led_shutdown();

    buffer = led_get_buffer();
    size_t count = led_get_pixel_count();
    print_test_result("Cleanup successful", buffer == NULL && count == 0);

    printf("\n=== Test Complete ===\n");
    return 0;
}