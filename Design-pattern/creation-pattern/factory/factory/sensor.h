#ifndef SENSOR_H
#define SENSOR_H

// Sensor structure with function pointers for initialization and reading data
typedef struct {
    void (*init)(void);      // Function to initialize the sensor
    float (*readData)(void); // Function to read data from the sensor
} Sensor;

#endif
