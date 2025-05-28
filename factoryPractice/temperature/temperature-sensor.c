#include <stdio.h>
#include "temperature-sensor.h"

void temperatureSensorInit() {
    printf("Temperature sensor initialized.\n");
}

float temperatureSensorReadData() {
    return 25.5; // Simulated value
}

// Create a temperature sensor object
Sensor createTemperatureSensor() {
    Sensor tempSensor;
    tempSensor.init = temperatureSensorInit;
    tempSensor.readData = temperatureSensorReadData;
    return tempSensor;
}