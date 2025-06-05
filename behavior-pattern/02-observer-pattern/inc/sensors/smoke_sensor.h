#ifndef SMOKE_SENSOR_H
#define SMOKE_SENSOR_H

#include "../publisher.h"

// Smoke sensor struct
typedef struct {
    Publisher base;
    int smokeDetected;
} SmokeSensor;

void smokeSensorInit(SmokeSensor* sensor);
void smokeSensorTrigger(SmokeSensor* sensor, int detected);

#endif // SMOKE_SENSOR_H
