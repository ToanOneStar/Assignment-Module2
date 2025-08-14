#include "factory.h"
#include "cpu-monitor.h"
#include "memory-monitor.h"
#include "network-monitor.h"
#include "storage-monitor.h"
#include "system-monitor.h"

/**
 * @brief Factory function to create a specific type of monitor.
 * 
 * Based on the provided MonitorType, this function creates and initializes
 * the corresponding monitor (CPU, Memory, Storage, Network, or System) and
 * returns it as a generic Monitor pointer.
 * 
 * @param type The type of monitor to create (MonitorType enum).
 * @return Monitor* Pointer to the newly created monitor, or NULL if the type is invalid.
 */
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