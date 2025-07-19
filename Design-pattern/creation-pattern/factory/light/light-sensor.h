#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "sensor.h"

void lightSensorInit();
float lightSensorReadData();
Sensor createLightSensor();

#endif // LIGHT_SENSOR_H