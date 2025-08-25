#include "storage-monitor.h"

/**
 * @brief Check storage usage and send alert if threshold is exceeded.
 * 
 * Calculates the percentage of used storage. If it exceeds the storage threshold,
 * creates an alert and notifies via the Monitor's notify system.
 * 
 * @param storage_monitor (in) Pointer to StorageMonitor containing current data and threshold.
 * @param self (in) Pointer to Monitor used to call notify for sending alerts.
 * 
 * @return void
 */
void alert_storage(StorageMonitor* storage_monitor, Monitor* self) {
    float storage_usage_percent = 100.0 * storage_monitor->data.used_space / storage_monitor->data.total_space;

    if (storage_usage_percent > storage_monitor->storage_threshold) {
        AlertData alert = {
            .level = ALERT_WARNING,
            .source = MONITOR_STORAGE,
            .timestamp = time(NULL),
        };
        snprintf(alert.message, sizeof(alert.message), "Storage usage high: %.1f%%", storage_usage_percent);
        self->subject->notify(self->subject, &alert);
    }
}

/**
 * @brief Collect storage data and update StorageMonitor structure.
 * 
 * Retrieves total, free, and used space for the root partition, generates
 * mock read/write speeds and IOPS, and triggers alerts if thresholds are exceeded.
 * 
 * @param self (in) Pointer to Monitor, cast to StorageMonitor inside the function.
 * 
 * @return void
 */
void collect_storage_data(Monitor* self) {
    StorageMonitor* storage_monitor = (StorageMonitor*)self;
    struct statvfs vfs;

    strncpy(storage_monitor->data.partition, "/", sizeof(storage_monitor->data.partition) - 1);

    if (statvfs("/", &vfs) == 0) {
        storage_monitor->data.total_space = vfs.f_blocks * vfs.f_frsize;
        storage_monitor->data.free_space = vfs.f_bavail * vfs.f_frsize;
        storage_monitor->data.used_space = storage_monitor->data.total_space - storage_monitor->data.free_space;
    }

    storage_monitor->data.read_speed = (rand() % 100) + 50;
    storage_monitor->data.write_speed = (rand() % 80) + 30;
    storage_monitor->data.iops = (rand() % 500) + 100;

    alert_storage(storage_monitor, self);
}

/**
 * @brief Create and initialize a StorageMonitor instance.
 * 
 * Allocates memory for StorageMonitor, initializes its base Monitor fields,
 * sets default storage usage threshold, and assigns function pointers for 
 * data collection and control.
 * 
 * @return Pointer to the newly created StorageMonitor instance.
 */
StorageMonitor* create_storage_monitor() {
    StorageMonitor* storage_monitor = (StorageMonitor*)malloc(sizeof(StorageMonitor));

    storage_monitor->base.type = MONITOR_STORAGE;
    storage_monitor->base.subject = create_subject();
    storage_monitor->base.running = 0;
    storage_monitor->base.collect_data = collect_storage_data;
    storage_monitor->base.start = monitor_start;
    storage_monitor->base.stop = monitor_stop;
    storage_monitor->storage_threshold = DEFAULT_STORAGE_THRESHOLD;

    return storage_monitor;
}