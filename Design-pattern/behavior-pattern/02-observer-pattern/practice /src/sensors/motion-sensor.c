#include <stdio.h>
#include "motion-sensor.h"

void motionSensorInit(MotionSensor* sensor) {
    publisherInit(&sensor->base);
    sensor->motionDetected = 0;
}

void motionSensorTrigger(MotionSensor* sensor, int detected) {
    sensor->motionDetected = detected;

    if (detected) {
        sensor->base.notifySubscribers(&sensor->base, "Motion is detected in the living room");
    } else {
        sensor->base.notifySubscribers(&sensor->base, "Motion isn't detected");
    }
}