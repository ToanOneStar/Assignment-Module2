#include <stdlib.h>
#include <string.h>
#include "logger.h"

#define SIZE_OF_USER_MESSAGE 1024
#define SIZE_OF_LOG_BUFFER   1536
#define SIZE_OF_TIMESTAMP    32

const char* logLevelNames[] = {
    "EMERGENCY",
    "ALERT",
    "CRITICAL",
    "ERROR",
    "WARNING",
    "NOTICE",
    "INFORMATIONAL",
    "DEBUG",
};

static const char* getFileName(const char* filepath) {
    const char* fileName = strrchr(filepath, '/');
    if (fileName == NULL) {
        fileName = strrchr(filepath, '\\');
    }

    return (fileName != NULL) ? fileName + 1 : filepath;
}

static void getTimestamp(char* buffer, size_t buffersize) {
    time_t now = time(NULL);
    struct tm* timeInfo = localtime(&now);

    strftime(buffer, buffersize, "%Y-%m-%d %H:%M:%S", timeInfo);
}

static const char* convertStringLevel(LogLevel level) {
    if (level >= LOG_EMERGENCY && level <= LOG_DEBUG) {
        return logLevelNames[level];
    }

    return "INVALID";
}

void logMessage(LogLevel level, const char* file, int line, const char* format, ...) {
    char timestamp[SIZE_OF_TIMESTAMP];
    getTimestamp(timestamp, sizeof(timestamp));

    const char* filename = getFileName(file);
    const char* stringLevel = convertStringLevel(level);

    va_list args;
    va_start(args, format);
    char user_message[SIZE_OF_USER_MESSAGE];
    vsnprintf(user_message, sizeof(user_message), format, args);
    va_end(args);

    char logLine[SIZE_OF_LOG_BUFFER];
    snprintf(logLine,
             sizeof(logLine),
             "[%s] [%s] [%s:%d] - %s\n",
             timestamp,
             stringLevel,
             filename,
             line,
             user_message);

    printf("%s", logLine);

    FILE* logFile = fopen("log.txt", "a");
    if (logFile != NULL) {
        fprintf(logFile, "%s", logLine);
        fclose(logFile);
    }
}