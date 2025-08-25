#include "system-monitor.h"

/**
 * @brief Collect system data and update SystemMonitor structure.
 * 
 * Retrieves system uptime, load averages, current system time, kernel version,
 * and counts the number of running services by scanning /proc.
 * 
 * @param self (in) Pointer to Monitor, cast to SystemMonitor inside the function.
 * 
 * @return void
 */
void collect_system_data(Monitor* self) {
    SystemMonitor* sys_monitor = (SystemMonitor*)self;
    struct sysinfo info;

    if (sysinfo(&info) == 0) {
        sys_monitor->data.uptime = info.uptime;
        sys_monitor->data.load_avg_1 = info.loads[0] / 65536.0;
        sys_monitor->data.load_avg_5 = info.loads[1] / 65536.0;
        sys_monitor->data.load_avg_15 = info.loads[2] / 65536.0;
    }

    sys_monitor->data.system_time = time(NULL);

    FILE* fp = fopen("/proc/version", "r");
    if (fp != NULL) {
        fgets(sys_monitor->data.kernel_version, sizeof(sys_monitor->data.kernel_version), fp);
        fclose(fp);
    }

    sys_monitor->data.running_services = 0;
    DIR* proc_dir = opendir("/proc");

    if (proc_dir) {
        struct dirent* entry;
        while ((entry = readdir(proc_dir)) != NULL) {
            if (strspn(entry->d_name, "0123456789") == strlen(entry->d_name)) {
                sys_monitor->data.running_services++;
            }
        }
        closedir(proc_dir);
    }
}

/**
 * @brief Create and initialize a SystemMonitor instance.
 * 
 * Allocates memory for SystemMonitor, initializes its base Monitor fields,
 * and assigns function pointers for data collection and control.
 * 
 * @return Pointer to the newly created SystemMonitor instance.
 */
SystemMonitor* create_system_monitor() {
    SystemMonitor* sys_monitor = (SystemMonitor*)malloc(sizeof(SystemMonitor));

    sys_monitor->base.type = MONITOR_SYSTEM;
    sys_monitor->base.subject = create_subject();
    sys_monitor->base.running = 0;
    sys_monitor->base.collect_data = collect_system_data;
    sys_monitor->base.start = monitor_start;
    sys_monitor->base.stop = monitor_stop;

    return sys_monitor;
}