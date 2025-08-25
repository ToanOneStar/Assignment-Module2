#include <stdio.h>
#include "humidity-sensor.h"

void humiditySensorInit() {
    printf("Humidity sensor initialized\n");
}

float humiditySensorReadData() {
    return 60.0;
}

Sensor createHumiditySensor() {
    Sensor humiditySensor;
    humiditySensor.init = humiditySensorInit;
    humiditySensor.readData = humiditySensorReadData;
    return humiditySensor;
}