#ifndef CONFIG_H
#define CONFIG_H

#include "common.h"

#define DEFAULT_CPU_THRESHOLD       80.0
#define DEFAULT_TEMP_THRESHOLD      70.0
#define DEFAULT_BANDWIDTH_THRESHOLD 1000.0
#define DEFAULT_REFRESH_INTERVAL    2
#define DEFAULT_MEMORY_THRESHOLD    85.0
#define DEFAULT_STORAGE_THRESHOLD   90.0
#define PORT                        8080

typedef struct {
    float cpu_threshold;
    float memory_threshold;
    float storage_threshold;
    float bandwidth_threshold;
    float temperature_threshold;
    int refresh_interval;
    char log_file[MAX_STRING_LEN];
    int api_port;
} SystemConfig;

SystemConfig* load_config(const char* filename);
void save_config(SystemConfig* config, const char* filename);

#endif // CONFIG_H