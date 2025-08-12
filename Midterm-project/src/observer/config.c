#include "config.h"

SystemConfig* load_config(const char* filename) {
    SystemConfig* config = malloc(sizeof(SystemConfig));

    config->cpu_threshold = DEFAULT_CPU_THRESHOLD;
    config->memory_threshold = DEFAULT_MEMORY_THRESHOLD;
    config->storage_threshold = DEFAULT_STORAGE_THRESHOLD;
    config->bandwidth_threshold = DEFAULT_BANDWIDTH_THRESHOLD;
    config->temperature_threshold = DEFAULT_TEMP_THRESHOLD;
    config->refresh_interval = DEFAULT_REFRESH_INTERVAL;
    strcpy(config->log_file, "monitoring.log");
    config->api_port = PORT;

    FILE* fp = fopen(filename, "r");
    if (fp != NULL) {
        char buffer[MAX_STRING_LEN];
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strncmp(buffer, "cpu_threshold=", 14) == 0) {
                sscanf(buffer, "cpu_threshold=%f", &config->cpu_threshold);
            } else if (strncmp(buffer, "memory_threshold=", 17) == 0) {
                sscanf(buffer, "memory_threshold=%f", &config->memory_threshold);
            } else if (strncmp(buffer, "storage_threshold=", 18) == 0) {
                sscanf(buffer, "storage_threshold=%f", &config->storage_threshold);
            } else if (strncmp(buffer, "bandwidth_threshold=", 20) == 0) {
                sscanf(buffer, "bandwidth_threshold=%f", &config->bandwidth_threshold);
            } else if (strncmp(buffer, "temperature_threshold=", 22) == 0) {
                sscanf(buffer, "temperature_threshold=%f", &config->temperature_threshold);
            } else if (strncmp(buffer, "refresh_interval=", 17) == 0) {
                sscanf(buffer, "refresh_interval=%d", &config->refresh_interval);
            } else if (strncmp(buffer, "log_file=", 9) == 0) {
                sscanf(buffer, "log_file=%s", config->log_file);
            } else if (strncmp(buffer, "api_port=", 9) == 0) {
                sscanf(buffer, "api_port=%d", &config->api_port);
            }
        }
        fclose(fp);
        printf("Configuration loaded from %s\n", filename);
    } else {
        printf("Configuration file not found, using defaults\n");
    }

    return config;
}

void save_config(SystemConfig* config, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp != NULL) {
        fprintf(fp, "# Embedded Monitoring System Configuration\n");
        fprintf(fp, "cpu_threshold=%.1f\n", config->cpu_threshold);
        fprintf(fp, "memory_threshold=%.1f\n", config->memory_threshold);
        fprintf(fp, "storage_threshold=%.1f\n", config->storage_threshold);
        fprintf(fp, "bandwidth_threshold=%.1f\n", config->bandwidth_threshold);
        fprintf(fp, "temperature_threshold=%.1f\n", config->temperature_threshold);
        fprintf(fp, "refresh_interval=%d\n", config->refresh_interval);
        fprintf(fp, "log_file=%s\n", config->log_file);
        fprintf(fp, "api_port=%d\n", config->api_port);
        fclose(fp);
        printf("Configuration saved to %s\n", filename);
    }
}