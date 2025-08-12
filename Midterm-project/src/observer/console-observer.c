#include "console-observer.h"
#include "cpu-monitor.h"
#include "memory-monitor.h"
#include "network-monitor.h"
#include "storage-monitor.h"
#include "system-monitor.h"

#define GB 1024.0 * 1024.0 * 1024.0

void console_update(Observer* self, Subject* subject, void* data) {
    AlertData* alert = (AlertData*)data;

    if (alert) {
        const char* level_str[] = {
            "INFO",
            "WARNING",
            "CRITICAL",
        };
        const char* source_str[] = {
            "CPU",
            "MEMORY",
            "STORAGE",
            "NETWORK",
            "SYSTEM",
        };

        printf("\n ALERT [%s] %s: %s\n", level_str[alert->level], source_str[alert->source], alert->message);

        if (alert->level == ALERT_CRITICAL) {
            system("echo -e '\\a'");
        }
    }
}

void display_monitoring_data(ConsoleObserver* console) {
    system("clear");
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                      EMBEDDED MONITORING SYSTEM v1.0                         ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ Refresh Rate: %d seconds                       Time: %s",
           REFRESH_INTERVAL,
           ctime(&(time_t){time(NULL)}));
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n\n");

    for (int i = 0; i < console->monitor_count; i++) {
        Monitor* monitor = console->monitors[i];

        switch (monitor->type) {
            case MONITOR_CPU: {
                CPUMonitor* cpu = (CPUMonitor*)monitor;

                printf("┌─ CPU MONITORING ─────────────────────────────────────────────────────────────┐\n");
                printf("│ Usage: %.1f%%    Cores: %d    Frequency: %.1f MHz    Temperature: %.1f°C    \n",
                       cpu->data.total_usage,
                       cpu->data.core_count,
                       cpu->data.frequency,
                       cpu->data.temperature);
                printf("│ Top Processes Use CPU:                                                                \n");

                for (int j = 0; j < MAX_PROCESSES; j++) {
                    if (cpu->data.top_cpu_usage_process[j].pid > 0) {
                        printf("│   %d. %-20s (PID: %d) - CPU: %.1f%% MEM: %.1f%%                     \n",
                               j + 1,
                               cpu->data.top_cpu_usage_process[j].name,
                               cpu->data.top_cpu_usage_process[j].pid,
                               cpu->data.top_cpu_usage_process[j].cpu_usage,
                               cpu->data.top_cpu_usage_process[j].memory_usage);
                    }
                }
                printf("└──────────────────────────────────────────────────────────────────────────────┘\n\n");
                break;
            }

            case MONITOR_MEMORY: {
                MemoryMonitor* mem = (MemoryMonitor*)monitor;

                printf("┌─ MEMORY MONITORING ──────────────────────────────────────────────────────────┐\n");
                printf("│ RAM: %.1f GB / %.1f GB (%.1f%%)    Swap: %.1f GB / %.1f GB              \n",
                       mem->data.used_ram / GB,
                       mem->data.total_ram / GB,
                       100.0 * mem->data.used_ram / mem->data.total_ram,
                       mem->data.swap_used / GB,
                       mem->data.swap_total / GB);
                printf("│ Cache: %.1f GB    Buffers: %.1f GB                                         \n",
                       mem->data.cache / GB,
                       mem->data.buffers / GB);
                printf("│ Top Processes Use RAM:                                                                \n");

                for (int j = 0; j < MAX_PROCESSES; j++) {
                    if (mem->data.top_ram_usage_process[j].pid > 0) {
                        printf("│   %d. %-20s (PID: %d) - CPU: %.1f%% MEM: %.1f%%                     \n",
                               j + 1,
                               mem->data.top_ram_usage_process[j].name,
                               mem->data.top_ram_usage_process[j].pid,
                               mem->data.top_ram_usage_process[j].cpu_usage,
                               mem->data.top_ram_usage_process[j].memory_usage);
                    }
                }
                printf("└───────────────────────────────────────────────────────────────────────────────┘\n\n");
                break;
            }

            case MONITOR_STORAGE: {
                StorageMonitor* storage = (StorageMonitor*)monitor;

                printf("┌─ STORAGE MONITOR ──────────────────────────────────────────────────────────┐\n");
                printf("│ Partition: %s                                                               \n",
                       storage->data.partition);
                printf("│ Space: %.1f GB / %.1f GB (%.1f%% used)                                     \n",
                       storage->data.used_space / GB,
                       storage->data.total_space / GB,
                       100.0 * storage->data.used_space / storage->data.total_space);
                printf("│ I/O: Read %.1f MB/s    Write %.1f MB/s    IOPS: %lu                        \n",
                       storage->data.read_speed,
                       storage->data.write_speed,
                       storage->data.iops);
                printf("└────────────────────────────────────────────────────────────────────────────┘\n\n");
                break;
            }

            case MONITOR_NETWORK: {
                NetworkMonitor* net = (NetworkMonitor*)monitor;

                printf("┌─ NETWORK MONITORING ─────────────────────────────────────────────────────────┐\n");
                printf("│ Active Connections: %d    Total Bandwidth: %.1f KB/s                       \n",
                       net->data.active_connections,
                       net->data.total_bandwidth_usage);
                printf("│ Network Interfaces:                                                           \n");

                for (int j = 0; j < net->data.interface_count; j++) {
                    NetworkInterface* iface = &net->data.interfaces[j];
                    printf("│   %-10s - IP: %-15s UP: %.1f KB/s DOWN: %.1f KB/s                      \n",
                           iface->interface,
                           iface->ip_address,
                           iface->upload_speed,
                           iface->download_speed);
                }
                printf("└──────────────────────────────────────────────────────────────────────────────┘\n\n");
                break;
            }

            case MONITOR_SYSTEM: {
                SystemMonitor* sys = (SystemMonitor*)monitor;

                printf("┌─ SYSTEM MONITORING ──────────────────────────────────────────────────────────┐\n");
                printf("│ Uptime: %ld hours %ld minutes                                              \n",
                       sys->data.uptime / 3600,
                       (sys->data.uptime % 3600) / 60);
                printf("│ Load Average: %.2f (1m)  %.2f (5m)  %.2f (15m)                             \n",
                       sys->data.load_avg_1,
                       sys->data.load_avg_5,
                       sys->data.load_avg_15);
                printf("│ Running Services: %d                                                         \n",
                       sys->data.running_services);
                printf("│ Kernel: %.50s                                               \n", sys->data.kernel_version);
                printf("└──────────────────────────────────────────────────────────────────────────────┘\n\n");
                break;
            }
        }
    }
}

ConsoleObserver* create_console_observer(Monitor** monitors, int count) {
    ConsoleObserver* console = (ConsoleObserver*)malloc(sizeof(ConsoleObserver));

    strcpy(console->base.name, "ConsoleDisplay");
    console->base.update = console_update;
    console->monitors = monitors;
    console->monitor_count = count;

    return console;
}
