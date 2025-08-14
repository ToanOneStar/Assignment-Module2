#include "cpu-monitor.h"

/**
 * @brief Check CPU status and send alerts if thresholds are exceeded.
 * 
 * Checks total CPU usage and temperature against defined thresholds.
 * If any value exceeds the limit, an alert is created and sent via Monitor.
 * 
 * @param cpu_monitor (in) Pointer to CpuMonitor containing current data and thresholds.
 * @param self (in) Pointer to Monitor used to call notify for sending alerts.
 * 
 * @return void
 */
void alert_cpu(CpuMonitor* cpu_monitor, Monitor* self) {
    if (cpu_monitor->data.total_usage > cpu_monitor->cpu_threshold) {
        AlertData alert = {
            .level = ALERT_WARNING,
            .source = MONITOR_CPU,
            .timestamp = time(NULL),
        };

        snprintf(alert.message, sizeof(alert.message), "CPU usage high: %.1f%%", cpu_monitor->data.total_usage);
        self->subject->notify(self->subject, &alert);
    }

    if (cpu_monitor->data.temperature > cpu_monitor->temp_threshold) {
        AlertData alert = {
            .level = ALERT_CRITICAL,
            .source = MONITOR_CPU,
            .timestamp = time(NULL),
        };

        snprintf(alert.message, sizeof(alert.message), "CPU temperature critical: %.1f°C", cpu_monitor->data.temperature);
        self->subject->notify(self->subject, &alert);
    }
}

/**
 * @brief Collect CPU data and update CpuMonitor structure.
 * 
 * Reads CPU usage and other statistics from /proc/stat, estimates total CPU usage,
 * counts cores, generates mock temperature and frequency values, and collects 
 * top 5 CPU-consuming processes. Calls alert function if thresholds are exceeded.
 * 
 * @param self (in) Pointer to Monitor, cast to CpuMonitor inside the function.
 * 
 * @return void
 */
void collect_cpu_data(Monitor* self) {
    CpuMonitor* cpu_monitor = (CpuMonitor*)self;

    FILE* fp;
    char buffer[MAX_STRING_LEN];
    fp = fopen("/proc/stat", "r");
    if (fp != NULL) {
        fgets(buffer, sizeof(buffer), fp);
        unsigned long user, nice, system, idle, iowait, irq, softirq;
        sscanf(buffer, "cpu %lu %lu %lu %lu %lu %lu %lu", &user, &nice, &system, &idle, &iowait, &irq, &softirq);

        unsigned long total = user + nice + system + idle + iowait + irq + softirq;
        unsigned long work = user + nice + system + irq + softirq;
        static unsigned long prev_total = 0, prev_work = 0;

        if (prev_total > 0) {
            cpu_monitor->data.total_usage = 100.0 * (work - prev_work) / (total - prev_total);
        }

        prev_total = total;
        prev_work = work;
        fclose(fp);
    }

    cpu_monitor->data.core_count = sysconf(_SC_NPROCESSORS_ONLN);
    cpu_monitor->data.temperature = 45.0 + (rand() % 20);
    cpu_monitor->data.frequency = 2400.0 + (rand() % 400);

    system("ps aux --sort=-%cpu | head -6 | tail -5 > /tmp/cpu_processes.txt");
    fp = fopen("/tmp/cpu_processes.txt", "r");

    if (fp != NULL) {
        for (int i = 0; i < MAX_PROCESSES && fgets(buffer, sizeof(buffer), fp); i++) {
            sscanf(buffer,
                   "%*s %d %f %f %*s %*s %*s %*s %*s %*s %*s %s",
                   &cpu_monitor->data.top_cpu_usage_process[i].pid,
                   &cpu_monitor->data.top_cpu_usage_process[i].cpu_usage,
                   &cpu_monitor->data.top_cpu_usage_process[i].memory_usage,
                   cpu_monitor->data.top_cpu_usage_process[i].name);
        }
        fclose(fp);
    }

    alert_cpu(cpu_monitor, self);
}

/**
 * @brief Create and initialize a CpuMonitor instance.
 * 
 * Allocates memory for CpuMonitor, initializes its base Monitor fields,
 * sets default CPU usage and temperature thresholds, and assigns function pointers
 * for data collection and control.
 * 
 * @return Pointer to the newly created CpuMonitor instance.
 */
CpuMonitor* create_cpu_monitor() {
    CpuMonitor* cpu_monitor = (CpuMonitor*)malloc(sizeof(CpuMonitor));

    cpu_monitor->base.type = MONITOR_CPU;
    cpu_monitor->base.subject = create_subject();
    cpu_monitor->base.running = 0;
    cpu_monitor->base.collect_data = collect_cpu_data;
    cpu_monitor->base.start = monitor_start;
    cpu_monitor->base.stop = monitor_stop;
    cpu_monitor->cpu_threshold = DEFAULT_CPU_THRESHOLD;
    cpu_monitor->temp_threshold = DEFAULT_TEMP_THRESHOLD;

    return cpu_monitor;
}