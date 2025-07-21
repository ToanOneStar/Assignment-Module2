#include <stdio.h>
#include "smoke-sensor.h"

void smokeSensorInit(SmokeSensor* sensor) {
    publisherInit(&sensor->base);
    sensor->smokeDetected = 0;
}

void smokeSensorTrigger(SmokeSensor* sensor, int detected) {
    sensor->smokeDetected = detected;

    if (detected) {
        sensor->base.notifySubscribers(&sensor->base, "Smoke Detected");
    } else {
        sensor->base.notifySubscribers(&sensor->base, "No smoke");
    }
}