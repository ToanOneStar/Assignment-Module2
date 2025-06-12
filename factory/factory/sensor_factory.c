#include <stdlib.h>
#include "../humidity/humidity-sensor.h"
#include "../light/light-sensor.h"
#include "../pressure/pressure_sensor.h"
#include "../temperature/temperature-sensor.h"
#include "sensor_factory.h"

// Factory method to create a sensor based on the provided type
Sensor* createSensor(SensorType type) {
    Sensor* sensor = (Sensor*)malloc(sizeof(Sensor));
    if (sensor == NULL) {
        return NULL;
    }

    switch (type) {
        case SENSOR_TEMPERATURE: *sensor = createTemperatureSensor(); break;
        case SENSOR_HUMIDITY: *sensor = createHumiditySensor(); break;
        case SENSOR_LIGHT: *sensor = createLightSensor(); break;
        case SENSOR_PRESSURE: *sensor = createPressureSensor(); break;
        default: free(sensor); return NULL; // Invalid sensor type
    }

    return sensor;
}
