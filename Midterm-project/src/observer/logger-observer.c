#include "logger-observer.h"

/**
 * @brief Log alert data to a file.
 * 
 * Formats the alert information with timestamp, level, source, and message,
 * then writes it to the log file associated with the LoggerObserver.
 * 
 * @param self (in) Pointer to Observer (LoggerObserver) receiving the alert.
 * @param subject (in) Pointer to Subject sending the alert (not used directly).
 * @param data (in) Pointer to AlertData containing the alert details.
 * 
 * @return void
 */
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

/**
 * @brief Create and initialize a LoggerObserver.
 * 
 * Allocates a LoggerObserver, sets its name and update callback, and opens
 * the specified log file in append mode for recording alerts.
 * 
 * @param filename (in) Path to the log file.
 * 
 * @return Pointer to the initialized LoggerObserver.
 *         If the file cannot be opened, a warning is printed and log_file is NULL.
 */
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

/**
 * @brief Clean up and free a LoggerObserver.
 * 
 * Closes the log file if it is open and frees the memory allocated for
 * the LoggerObserver.
 * 
 * @param logger (in) Pointer to the LoggerObserver to be cleaned up.
 * 
 * @return void
 */
void cleanup_logger_observer(LoggerObserver* logger) {
    if (logger->log_file) {
        fclose(logger->log_file);
    }
    free(logger);
}