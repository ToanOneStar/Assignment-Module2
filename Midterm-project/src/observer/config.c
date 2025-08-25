#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_FLOAT,
    TYPE_INT,
    TYPE_STRING,
} ConfigType;

typedef struct {
    const char* key;
    ConfigType type;
    void* dest;
    const char* read_format;
    const char* write_format;
} ConfigMap;

/**
 * @brief Initialize SystemConfig with default values.
 * 
 * Sets default thresholds for CPU, memory, storage, bandwidth, and temperature,
 * as well as default refresh interval, log file name, and API port.
 * 
 * @param cfg (out) Pointer to SystemConfig structure to initialize.
 * 
 * @return void
 */
static void set_default_config(SystemConfig* cfg) {
    cfg->cpu_threshold = DEFAULT_CPU_THRESHOLD;
    cfg->memory_threshold = DEFAULT_MEMORY_THRESHOLD;
    cfg->storage_threshold = DEFAULT_STORAGE_THRESHOLD;
    cfg->bandwidth_threshold = DEFAULT_BANDWIDTH_THRESHOLD;
    cfg->temperature_threshold = DEFAULT_TEMP_THRESHOLD;
    cfg->refresh_interval = DEFAULT_REFRESH_INTERVAL;
    strcpy(cfg->log_file, "monitoring.log");
    cfg->api_port = PORT;
}

/**
 * @brief Create a mapping between configuration fields and their string representations.
 * 
 * Populates an array of ConfigMap structures linking each field in SystemConfig
 * to its type, destination pointer, and format strings for reading/writing.
 * Optionally returns the number of entries via the count parameter.
 * 
 * @param config (in/out) Pointer to SystemConfig containing the actual configuration values.
 * @param count (out, optional) Pointer to size_t to store the number of mapping entries.
 * 
 * @return Pointer to a static array of ConfigMap structures.
 */
static ConfigMap* get_config_map(SystemConfig* config, size_t* count) {
    static ConfigMap map[] = {
        {"cpu_threshold", TYPE_FLOAT, NULL, "cpu_threshold=%f", "cpu_threshold=%.1f\n"},
        {"memory_threshold", TYPE_FLOAT, NULL, "memory_threshold=%f", "memory_threshold=%.1f\n"},
        {"storage_threshold", TYPE_FLOAT, NULL, "storage_threshold=%f", "storage_threshold=%.1f\n"},
        {"bandwidth_threshold", TYPE_FLOAT, NULL, "bandwidth_threshold=%f", "bandwidth_threshold=%.1f\n"},
        {"temperature_threshold", TYPE_FLOAT, NULL, "temperature_threshold=%f", "temperature_threshold=%.1f\n"},
        {"refresh_interval", TYPE_INT, NULL, "refresh_interval=%d", "refresh_interval=%d\n"},
        {"log_file", TYPE_STRING, NULL, "log_file=%s", "log_file=%s\n"},
        {"api_port", TYPE_INT, NULL, "api_port=%d", "api_port=%d\n"}
    };

    map[0].dest = &config->cpu_threshold;
    map[1].dest = &config->memory_threshold;
    map[2].dest = &config->storage_threshold;
    map[3].dest = &config->bandwidth_threshold;
    map[4].dest = &config->temperature_threshold;
    map[5].dest = &config->refresh_interval;
    map[6].dest = config->log_file;
    map[7].dest = &config->api_port;

    if (count != NULL) {
        *count = sizeof(map) / sizeof(map[0]);
    }
    return map;
}

/**
 * @brief Load system configuration from a file, or use defaults if file not found.
 * 
 * Allocates a SystemConfig structure, sets default values, then attempts to
 * read configuration values from the specified file using the ConfigMap mapping.
 * 
 * @param filename (in) Path to the configuration file to read.
 * 
 * @return Pointer to the initialized SystemConfig structure, or NULL if allocation fails.
 */
SystemConfig* load_config(const char* filename) {
    SystemConfig* config = malloc(sizeof(SystemConfig));
    if (!config) {
        return NULL;
    }
    set_default_config(config);

    size_t count;
    ConfigMap* config_map = get_config_map(config, &count);

    FILE* fp = fopen(filename, "r");
    if (fp) {
        char buffer[MAX_STRING_LEN];
        while (fgets(buffer, sizeof(buffer), fp)) {
            for (size_t i = 0; i < count; ++i) {
                size_t key_len = strlen(config_map[i].key);
                if (strncmp(buffer, config_map[i].key, key_len) == 0) {
                    sscanf(buffer, config_map[i].read_format, config_map[i].dest);
                    break;
                }
            }
        }
        fclose(fp);
        printf("Configuration loaded from %s\n", filename);
    } else {
        printf("Configuration file not found, using defaults\n");
    }

    return config;
}

/**
 * @brief Save the current system configuration to a file.
 * 
 * Writes all configuration fields from SystemConfig to the specified file
 * using the mappings defined in ConfigMap and the appropriate format strings.
 * 
 * @param config (in) Pointer to the SystemConfig to save.
 * @param filename (in) Path to the file where configuration should be written.
 * 
 * @return void
 */
void save_config(SystemConfig* config, const char* filename) {
    size_t count;
    ConfigMap* config_map = get_config_map(config, &count);

    FILE* fp = fopen(filename, "w");
    if (!fp) {
        return;
    }

    fprintf(fp, "# Embedded Monitoring System Configuration\n");

    for (size_t i = 0; i < count; i++) {
        switch (config_map[i].type) {
            case TYPE_FLOAT:
                fprintf(fp, config_map[i].write_format, *(float*)config_map[i].dest);
                break;
            case TYPE_INT:
                fprintf(fp, config_map[i].write_format, *(int*)config_map[i].dest);
                break;
            case TYPE_STRING:
                fprintf(fp, config_map[i].write_format, (char*)config_map[i].dest);
                break;
        }
    }

    fclose(fp);
    printf("Configuration saved to %s\n", filename);
}