#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "../factory/sensor.h"

void lightSensorInit();
float lightSensorReadData();
Sensor createLightSensor();

#endif
