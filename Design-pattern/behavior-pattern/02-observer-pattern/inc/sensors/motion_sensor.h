#ifndef Motion_SENSOR_H
#define Motion_SENSOR_H

#include "../publisher.h"

// Motion sensor struct
typedef struct
{
    Publisher base;
    int motionDetected;
} MotionSensor;

void motionSensorInit(MotionSensor *sensor);
void motionSensorTrigger(MotionSensor *sensor, int detected);

#endif // Motion_SENSOR_H
