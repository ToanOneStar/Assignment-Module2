#include <stdio.h>
#include "pressure-sensor.h"

void pressureSensorInit() {
    printf("Pressure sensor initialized.\n");
}

float pressureSensorReadData() {
    return 20.0; 
}

Sensor createPressureSensor() {
    Sensor pressureSensor;
    pressureSensor.init = pressureSensorInit;
    pressureSensor.readData = pressureSensorReadData;
    return pressureSensor;
}
