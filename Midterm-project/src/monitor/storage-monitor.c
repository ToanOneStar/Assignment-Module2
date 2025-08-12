#include "storage-monitor.h"

void storage_collect_data(Monitor* self) {
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

StorageMonitor* create_storage_monitor() {
    StorageMonitor* storage_monitor = (StorageMonitor*)malloc(sizeof(StorageMonitor));

    storage_monitor->base.type = MONITOR_STORAGE;
    storage_monitor->base.subject = create_subject();
    storage_monitor->base.running = 0;
    storage_monitor->base.collect_data = storage_collect_data;
    storage_monitor->base.start = monitor_start;
    storage_monitor->base.stop = monitor_stop;
    storage_monitor->storage_threshold = DEFAULT_STORAGE_THRESHOLD;

    return storage_monitor;
}