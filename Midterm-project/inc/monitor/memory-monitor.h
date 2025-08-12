#ifndef MEMORY_MONITOR_H
#define MEMORY_MONITOR_H

#include "monitor.h"

typedef struct {
    Monitor base;
    MemoryData data;
    float memory_threshold;
} MemoryMonitor;

void memory_collect_data(Monitor* self);
MemoryMonitor* create_memory_monitor();

#endif // MEMORY_MONITOR_H