#ifndef WATERING_LOGIC_H
#define WATERING_LOGIC_H

#include "config.h"

void watering_logic_init(system_config_t* config, system_state_t* state);
void watering_logic_process(system_config_t* config, system_state_t* state, sensor_data_t* sensor_data);
bool should_start_watering(const system_config_t* config, const system_state_t* state,
                           const sensor_data_t* sensor_data);
bool should_stop_watering(const system_config_t* config, const system_state_t* state, const sensor_data_t* sensor_data);
void start_manual_watering(system_state_t* state);
void update_led_status(system_config_t* config, system_state_t* state, sensor_data_t* sensor_data);

#endif // WATERING_LOGIC_H