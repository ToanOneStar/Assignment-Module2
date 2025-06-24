#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

typedef enum {
    LOG_EMERGENCY = 0,
    LOG_ALERT,
    LOG_CRITICAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;

void logMessage(LogLevel level, const char* file, int line, const char* _get_output_format, ...);

#define log_message(level, format, ...) logMessage(level, __FILE__, __LINE__, format, ##__VA_ARGS__)

#endif // LOGGER_H