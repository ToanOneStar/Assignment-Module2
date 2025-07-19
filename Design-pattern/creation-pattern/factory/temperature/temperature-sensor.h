#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "sensor.h"

void temperatureSensorInit();
float temperatureSensorReadData();
Sensor createTemperatureSensor();

#endif // TEMPERATURE_SENSOR_H