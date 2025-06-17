#ifndef SENSORS_H
#define SENSORS_H

#include "config.h"

void sensors_init(void);
bool sensors_read_data(sensor_data_t* data);
uint8_t sensors_get_soil_moisture(void);
int16_t sensors_get_temperature(void);
bool sensors_is_data_valid(const sensor_data_t* data);

#endif // SENSORS_H