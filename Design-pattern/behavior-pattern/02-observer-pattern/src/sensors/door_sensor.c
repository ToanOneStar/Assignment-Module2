#include "../../inc/sensors/door_sensor.h"
#include <stdio.h>

// Initialize the DoorSensor struct
void doorSensorInit(DoorSensor* sensor) {
    publisherInit(&sensor->base);
    sensor->isOpen = 0;
}

// Simulate a door event and notify subscribers
void doorSensorTrigger(DoorSensor* sensor, int open) {
    sensor->isOpen = open;
    if (open) {
        sensor->base.notifySubscribers(&sensor->base, "Door Opened");
    } else {
        sensor->base.notifySubscribers(&sensor->base, "Door Closed");
    }
}