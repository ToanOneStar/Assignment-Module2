#ifndef DOOR_SENSOR_H
#define DOOR_SENSOR_H

#include "../publisher.h"

// Door sensor struct
typedef struct
{
    Publisher base;
    int isOpen;
} DoorSensor;

void doorSensorInit(DoorSensor *sensor);
void doorSensorTrigger(DoorSensor *sensor, int open);

#endif // DOOR_SENSOR_H
