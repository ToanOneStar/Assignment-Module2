#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"
#include "observer.h"

typedef struct {
    float total_usage;
    float core_usage[8];
    int core_count;
    float frequency;
    float temperature;
    ProcessInfo top_cpu_usage_process[MAX_PROCESSES];
} CPUData;

typedef struct {
    unsigned long total_ram;
    unsigned long used_ram;
    unsigned long free_ram;
    unsigned long swap_total;
    unsigned long swap_used;
    unsigned long cache;
    unsigned long buffers;
    ProcessInfo top_ram_usage_process[MAX_PROCESSES];
} MemoryData;

typedef struct {
    char partition[MAX_STRING_LEN];
    unsigned long total_space;
    unsigned long used_space;
    unsigned long free_space;
    float read_speed;
    float write_speed;
    unsigned long iops;
} StorageData;

typedef struct {
    char interface[MAX_STRING_LEN];
    char ip_address[INET_ADDRSTRLEN];
    unsigned long bytes_sent;
    unsigned long bytes_recv;
    unsigned long packets_sent;
    unsigned long packets_recv;
    float upload_speed;
    float download_speed;
} NetworkInterface;

typedef struct {
    NetworkInterface interfaces[MAX_INTERFACES];
    int interface_count;
    int active_connections;
    float total_bandwidth_usage;
} NetworkData;

typedef struct {
    long uptime;
    time_t system_time;
    char kernel_version[MAX_STRING_LEN];
    float load_avg_1;
    float load_avg_5;
    float load_avg_15;
    int running_services;
} SystemData;

typedef struct Monitor {
    MonitorType type;
    Subject* subject;
    pthread_t thread;
    int running;
    void (*collect_data)(struct Monitor* self);
    void (*start)(struct Monitor* self);
    void (*stop)(struct Monitor* self);
} Monitor;

void* monitor_thread(void* arg);
void monitor_start(Monitor* self);
void monitor_stop(Monitor* self);

#endif // MONITOR_H