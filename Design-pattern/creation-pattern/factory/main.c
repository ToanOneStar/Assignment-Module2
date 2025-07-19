#include <stdio.h>
#include <stdlib.h>
#include "humidity-sensor.h"
#include "light-sensor.h"
#include "pressure-sensor.h"
#include "sensor-factory.h"
#include "temperature-sensor.h"

int main() {
    Sensor* tempSensor = createSensor(SENSOR_TEMPERATURE);
    if (tempSensor != NULL) {
        tempSensor->init();
        printf("Temperature: %.2f°C\n", tempSensor->readData());
        free(tempSensor);
    }

    Sensor* humiditySensor = createSensor(SENSOR_HUMIDITY);
    if (humiditySensor != NULL) {
        humiditySensor->init();
        printf("Humidity: %.2f%%\n", humiditySensor->readData());
        free(humiditySensor);
    }

    Sensor* lightSensor = createSensor(SENSOR_LIGHT);
    if (lightSensor != NULL) {
        lightSensor->init();
        printf("Light Intensity: %.2f lux\n", lightSensor->readData());
        free(lightSensor);
    }

    Sensor* pressureSensor = createSensor(SENSOR_PRESSURE);
    if (pressureSensor != NULL) {
        pressureSensor->init();
        printf("Pressure: %.2f atm\n", pressureSensor->readData());
        free(pressureSensor);
    }

    return 0;
}