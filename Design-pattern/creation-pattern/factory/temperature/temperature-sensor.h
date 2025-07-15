#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "../factory/sensor.h"

void temperatureSensorInit();
float temperatureSensorReadData();
Sensor createTemperatureSensor();

#endif