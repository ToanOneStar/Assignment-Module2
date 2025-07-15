#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include "../factory/sensor.h"

void humiditySensorInit();
float humiditySensorReadData();
Sensor createHumiditySensor();

#endif
