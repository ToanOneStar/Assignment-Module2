#ifndef COMMON_H
#define COMMON_H

#include <arpa/inet.h>
#include <dirent.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <time.h>
#include <unistd.h>

#define MAX_OBSERVERS    10
#define MAX_PROCESSES    5
#define MAX_STRING_LEN   256
#define MAX_INTERFACES   10
#define REFRESH_INTERVAL 2

typedef enum {
    MONITOR_CPU,
    MONITOR_MEMORY,
    MONITOR_STORAGE,
    MONITOR_NETWORK,
    MONITOR_SYSTEM,
} MonitorType;

typedef enum {
    ALERT_INFO,
    ALERT_WARNING,
    ALERT_CRITICAL,
} AlertLevel;

typedef struct {
    int pid;
    char name[MAX_STRING_LEN];
    float cpu_usage;
    float memory_usage;
} ProcessInfo;

typedef struct {
    AlertLevel level;
    char message[MAX_STRING_LEN];
    time_t timestamp;
    MonitorType source;
} AlertData;

#endif // COMMON_H