#ifndef SENSOR_H
#define SENSOR_H

typedef struct {
    void (*init)(void);
    float (*readData)(void);
} Sensor;

#endif // SENSOR_H