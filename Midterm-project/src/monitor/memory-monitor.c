#include "memory-monitor.h"

void memory_collect_data(Monitor* self) {
    MemoryMonitor* mem_monitor = (MemoryMonitor*)self;
    struct sysinfo info;

    if (sysinfo(&info) == 0) {
        mem_monitor->data.total_ram = info.totalram * info.mem_unit;
        mem_monitor->data.free_ram = info.freeram * info.mem_unit;
        mem_monitor->data.used_ram = mem_monitor->data.total_ram - mem_monitor->data.free_ram;
        mem_monitor->data.swap_total = info.totalswap * info.mem_unit;
        mem_monitor->data.swap_used = (info.totalswap - info.freeswap) * info.mem_unit;
        mem_monitor->data.buffers = info.bufferram * info.mem_unit;
    }

    FILE* fp = fopen("/proc/meminfo", "r");

    if (fp != NULL) {
        char buffer[MAX_STRING_LEN];
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strncmp(buffer, "Cached:", 7) == 0) {
                sscanf(buffer, "Cached: %lu kB", &mem_monitor->data.cache);
                mem_monitor->data.cache *= 1024;
                break;
            }
        }
        fclose(fp);
    }

    system("ps aux --sort=-%mem | head -6 | tail -5 > /tmp/mem_processes.txt");
    fp = fopen("/tmp/mem_processes.txt", "r");

    if (fp != NULL) {
        char buffer[MAX_STRING_LEN];

        for (int i = 0; i < MAX_PROCESSES && fgets(buffer, sizeof(buffer), fp); i++) {
            sscanf(buffer,
                   "%*s %d %f %f %*s %*s %*s %*s %*s %*s %*s %s",
                   &mem_monitor->data.top_ram_usage_process[i].pid,
                   &mem_monitor->data.top_ram_usage_process[i].cpu_usage,
                   &mem_monitor->data.top_ram_usage_process[i].memory_usage,
                   mem_monitor->data.top_ram_usage_process[i].name);
        }
        fclose(fp);
    }

    float memory_usage_percent = 100.0 * mem_monitor->data.used_ram / mem_monitor->data.total_ram;

    if (memory_usage_percent > mem_monitor->memory_threshold) {
        AlertData alert = {
            .level = ALERT_WARNING,
            .source = MONITOR_MEMORY,
            .timestamp = time(NULL),
        };

        snprintf(alert.message, sizeof(alert.message), "Memory usage high: %.1f%%", memory_usage_percent);
        self->subject->notify(self->subject, &alert);
    }
}

MemoryMonitor* create_memory_monitor() {
    MemoryMonitor* mem_monitor = malloc(sizeof(MemoryMonitor));

    mem_monitor->base.type = MONITOR_MEMORY;
    mem_monitor->base.subject = create_subject();
    mem_monitor->base.running = 0;
    mem_monitor->base.collect_data = memory_collect_data;
    mem_monitor->base.start = monitor_start;
    mem_monitor->base.stop = monitor_stop;
    mem_monitor->memory_threshold = DEFAULT_MEMORY_THRESHOLD;

    return mem_monitor;
}