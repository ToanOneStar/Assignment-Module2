#include "factory.h"
#include "cpu-monitor.h"
#include "memory-monitor.h"
#include "network-monitor.h"
#include "storage-monitor.h"
#include "system-monitor.h"

Monitor* create_monitor(MonitorType type) {
    switch (type) {
        case MONITOR_CPU: return (Monitor*)create_cpu_monitor();
        case MONITOR_MEMORY: return (Monitor*)create_memory_monitor();
        case MONITOR_STORAGE: return (Monitor*)create_storage_monitor();
        case MONITOR_NETWORK: return (Monitor*)create_network_monitor();
        case MONITOR_SYSTEM: return (Monitor*)create_system_monitor();
        default: return NULL;
    }
}

MonitorFactory factory = {.create_monitor = create_monitor};