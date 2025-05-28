#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include "../factory/sensor.h"

// Function prototypes for the humidity sensor
void humiditySensorInit();
float humiditySensorReadData();
Sensor createHumiditySensor();

#endif
