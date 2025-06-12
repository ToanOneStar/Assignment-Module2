#include <stdio.h>
#include "pressure_sensor.h"

void pressureSensorInit() {
    printf("Pressure sensor initialized.\n");
}

float pressureSensorReadData() {
    return 20.0; // Simulated value
}

/*Create a pressure sensor object*/
Sensor createPressureSensor() {
    Sensor pressureSensor;
    pressureSensor.init = pressureSensorInit;
    pressureSensor.readData = pressureSensorReadData;
    return pressureSensor;
}
