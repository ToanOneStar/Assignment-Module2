#include <stdio.h>
#include "temperature-sensor.h"

void temperatureSensorInit(TemperatureSensor* sensor) {
    publisherInit(&sensor->base);
    sensor->overTemperature = 0;
}

void temperatureSensorTrigger(TemperatureSensor* sensor, int over) {
    sensor->overTemperature = over;

    if (over) {
        sensor->base.notifySubscribers(&sensor->base, "Temperature is over 35 degrees celsius");
    } else {
        sensor->base.notifySubscribers(&sensor->base, "Temperature is normal");
    }
}