#include "logger-observer.h"

void logger_update(Observer* self, Subject* subject, void* data) {
    LoggerObserver* logger = (LoggerObserver*)self;
    AlertData* alert = (AlertData*)data;

    if (alert && logger->log_file) {
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

        char timestamp[64];
        struct tm* tm_info = localtime(&alert->timestamp);
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

        fprintf(logger->log_file,
                "[%s] %s - %s: %s\n",
                timestamp,
                level_str[alert->level],
                source_str[alert->source],
                alert->message);
        fflush(logger->log_file);
    }
}

LoggerObserver* create_logger_observer(const char* filename) {
    LoggerObserver* logger = (LoggerObserver*)malloc(sizeof(LoggerObserver));

    strcpy(logger->base.name, "Logger");
    logger->base.update = logger_update;

    logger->log_file = fopen(filename, "a");
    if (!logger->log_file) {
        printf("Warning: Could not open log file %s\n", filename);
    }

    return logger;
}

void cleanup_logger_observer(LoggerObserver* logger) {
    if (logger->log_file) {
        fclose(logger->log_file);
    }
    free(logger);
}