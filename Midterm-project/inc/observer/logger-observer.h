#ifndef LOGGER_OBSERVER_H
#define LOGGER_OBSERVER_H

#include "observer.h"

typedef struct {
    Observer base;
    FILE* log_file;
} LoggerObserver;

LoggerObserver* create_logger_observer(const char* filename);

void logger_update(Observer* self, Subject* subject, void* data);
void cleanup_logger_observer(LoggerObserver* logger);

#endif // LOGGER_OBSERVER_H