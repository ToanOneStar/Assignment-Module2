#include "../../inc/sensors/smoke_sensor.h"
#include <stdio.h>

// Initialize the SmokeSensor struct
void smokeSensorInit(SmokeSensor* sensor) {
    publisherInit(&sensor->base);
    sensor->smokeDetected = 0;
}

// Simulate a smoke event and notify subscribers
void smokeSensorTrigger(SmokeSensor* sensor, int detected) {
    sensor->smokeDetected = detected;
    if (detected) {
        sensor->base.notifySubscribers(&sensor->base, "Smoke Detected");
    } else {
        sensor->base.notifySubscribers(&sensor->base, "No Smoke");
    }
}
