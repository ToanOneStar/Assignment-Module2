#include <stdio.h>
#include "../../inc/sensors/temperature_sensor.h"

// Initialize the TemperatureSensor struct
void temperatureSensorInit(TemperatureSensor* sensor) {
    publisherInit(&sensor->base);
    sensor->overTemperature = 0;
}

// Simulate a over temperature event and notify subscribers
void temperatureSensorTrigger(TemperatureSensor* sensor, int over) {
    sensor->overTemperature = over;
    if (over) {
        sensor->base.notifySubscribers(&sensor->base, "Temperature is over 35 degrees celsius");
    } else {
        sensor->base.notifySubscribers(&sensor->base, "Temperature is normal");
    }
}
