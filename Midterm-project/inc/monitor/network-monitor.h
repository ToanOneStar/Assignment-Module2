#ifndef NETWORK_MONITOR_H
#define NETWORK_MONITOR_H

#include "monitor.h"

typedef struct {
    Monitor base;
    NetworkData data;
    float bandwidth_threshold;
} NetworkMonitor;

void network_collect_data(Monitor* self);
NetworkMonitor* create_network_monitor();

#endif // NETWORK_MONITOR_H