#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include "sensor.h"

void pressureSensorInit();
float pressureSensorReadData();
Sensor createPressureSensor();

#endif // PRESSURE_SENSOR_H