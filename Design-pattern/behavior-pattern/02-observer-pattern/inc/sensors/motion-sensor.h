#ifndef MOTION_SENSOR_H
#define MOTION_SENSOR_H

#include "publisher.h"

typedef struct {
    Publisher base;
    int motionDetected;
} MotionSensor;

void motionSensorInit(MotionSensor* sensor);
void motionSensorTrigger(MotionSensor* sensor, int detected);

#endif // MOTION_SENSOR_H