#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

#include "monitor.h"

typedef struct {
    Monitor base;
    CPUData data;
    float cpu_threshold;
    float temp_threshold;
} CpuMonitor;

void collect_cpu_data(Monitor* self);
CpuMonitor* create_cpu_monitor();

#endif // CPU_MONITOR_H