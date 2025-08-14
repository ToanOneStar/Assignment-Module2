#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

#include "monitor.h"

typedef struct {
    Monitor base;
    SystemData data;
} SystemMonitor;

void collect_system_data(Monitor* self);
SystemMonitor* create_system_monitor();

#endif // SYSTEM_MONITOR_H