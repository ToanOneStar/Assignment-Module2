#include <stdio.h>
#include "door-sensor.h"

void doorSensorInit(DoorSensor* sensor) {
    publisherInit(&sensor->base);
    sensor->isOpen = 0;
}

void doorSensorTrigger(DoorSensor* sensor, int open) {
    sensor->isOpen = open;

    if (open) {
        sensor->base.notifySubscribers(&sensor->base, "Door Opened");
    } else {
        sensor->base.notifySubscribers(&sensor->base, "Door Closed");
    }
}