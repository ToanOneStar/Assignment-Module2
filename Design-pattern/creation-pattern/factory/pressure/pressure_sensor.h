#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include "../factory/sensor.h"

/*Function prototypes for the pressure sensor*/
void pressureSensorInit();
float pressureSensorReadData();
Sensor createPressureSensor();

#endif