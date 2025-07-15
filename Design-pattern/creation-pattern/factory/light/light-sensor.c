#include <stdio.h>
#include "light-sensor.h"

void lightSensorInit() {
    printf("Light sensor initialized.\n");
}

float lightSensorReadData() {
    return 300.0; 
}

Sensor createLightSensor() {
    Sensor lightSensor;
    lightSensor.init = lightSensorInit;
    lightSensor.readData = lightSensorReadData;
    return lightSensor;
}
