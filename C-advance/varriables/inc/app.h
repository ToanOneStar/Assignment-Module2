#ifndef APP_H
#define APP_H

#include "config.h"

extern system_config_t g_config;
extern system_state_t g_state;
extern sensor_data_t g_sensor_data;

void system_init(void);
void process_buttons(void);
void send_status_report(void);

#endif // APP_H