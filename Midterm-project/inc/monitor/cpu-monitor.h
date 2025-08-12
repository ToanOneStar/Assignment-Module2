#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

#include "monitor.h"

typedef struct {
    Monitor base;
    CPUData data;
    float cpu_threshold;
    float temp_threshold;
} CPUMonitor;

void cpu_collect_data(Monitor* self);
CPUMonitor* create_cpu_monitor();

#endif // CPU_MONITOR_H