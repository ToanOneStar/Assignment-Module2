#include <stdlib.h>
#include "humidity-sensor.h"
#include "light-sensor.h"
#include "pressure-sensor.h"
#include "sensor-factory.h"
#include "temperature-sensor.h"

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
        default: free(sensor); return NULL;
    }

    return sensor;
}