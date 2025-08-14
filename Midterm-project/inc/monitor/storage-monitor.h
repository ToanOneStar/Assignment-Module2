#ifndef STORAGE_MONITOR_H
#define STORAGE_MONITOR_H

#include "monitor.h"

typedef struct {
    Monitor base;
    StorageData data;
    float storage_threshold;
} StorageMonitor;

void collect_storage_data(Monitor* self);
StorageMonitor* create_storage_monitor();

#endif // STORAGE_MONITOR_H