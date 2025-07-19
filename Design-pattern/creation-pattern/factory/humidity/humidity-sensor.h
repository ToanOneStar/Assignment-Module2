#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include "sensor.h"

void humiditySensorInit();
float humiditySensorReadData();
Sensor createHumiditySensor();

#endif // HUMIDITY_SENSOR_H