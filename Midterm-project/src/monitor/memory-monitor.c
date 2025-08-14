#include "memory-monitor.h"

/**
 * @brief Check memory usage and send an alert if threshold is exceeded.
 * 
 * Calculates the percentage of used RAM. If it exceeds the memory threshold,
 * an alert is created and sent via the Monitor's notify system.
 * 
 * @param mem_monitor (in) Pointer to MemoryMonitor containing current memory data and threshold.
 * @param self (in) Pointer to Monitor used to call notify for sending alerts.
 * 
 * @return void
 */
void alert_memory(MemoryMonitor* mem_monitor, Monitor* self) {
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

/**
 * @brief Collect memory data and update MemoryMonitor structure.
 * 
 * Retrieves RAM and swap usage via sysinfo, reads cached memory from /proc/meminfo,
 * collects top 5 memory-consuming processes, and triggers memory alerts if thresholds are exceeded.
 * 
 * @param self (in) Pointer to Monitor, cast to MemoryMonitor inside the function.
 * 
 * @return void
 */
void collect_memory_data(Monitor* self) {
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

    alert_memory(mem_monitor, self);
}

/**
 * @brief Create and initialize a MemoryMonitor instance.
 * 
 * Allocates memory for MemoryMonitor, initializes its base Monitor fields,
 * sets default memory usage threshold, and assigns function pointers for 
 * data collection and control.
 * 
 * @return Pointer to the newly created MemoryMonitor instance.
 */
MemoryMonitor* create_memory_monitor() {
    MemoryMonitor* mem_monitor = malloc(sizeof(MemoryMonitor));

    mem_monitor->base.type = MONITOR_MEMORY;
    mem_monitor->base.subject = create_subject();
    mem_monitor->base.running = 0;
    mem_monitor->base.collect_data = collect_memory_data;
    mem_monitor->base.start = monitor_start;
    mem_monitor->base.stop = monitor_stop;
    mem_monitor->memory_threshold = DEFAULT_MEMORY_THRESHOLD;

    return mem_monitor;
}