#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "publisher.h"

typedef struct {
    Publisher base;
    int overTemperature;
} TemperatureSensor;

void temperatureSensorInit(TemperatureSensor* sensor);
void temperatureSensorTrigger(TemperatureSensor* sensor, int over);

#endif // TEMPERATURE_SENSOR_H
