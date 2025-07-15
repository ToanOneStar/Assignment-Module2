#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include "../factory/sensor.h"

void pressureSensorInit();
float pressureSensorReadData();
Sensor createPressureSensor();

#endif