#ifndef MONITORING_SYSTEM_H
#define MONITORING_SYSTEM_H

#include "api-observer.h"
#include "common.h"
#include "config.h"
#include "console-observer.h"
#include "logger-observer.h"
#include "monitor.h"

typedef struct {
    Monitor* monitors[5];
    ConsoleObserver* console;
    LoggerObserver* logger;
    ApiObserver* api;
    SystemConfig* config;
    int running;
} MonitoringSystem;

MonitoringSystem* create_monitoring_system();

void start_monitoring_system(MonitoringSystem* system);
void stop_monitoring_system(MonitoringSystem* system);
void cleanup_monitoring_system(MonitoringSystem* system);

#endif // MONITORING_SYSTEM_H