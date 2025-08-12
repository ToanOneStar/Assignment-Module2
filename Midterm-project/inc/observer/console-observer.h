#ifndef CONSOLE_OBSERVER_H
#define CONSOLE_OBSERVER_H

#include "observer.h"
#include "monitor.h"

typedef struct {
    Observer base;
    Monitor** monitors;
    int monitor_count;
} ConsoleObserver;

void console_update(Observer* self, Subject* subject, void* data);
void display_monitoring_data(ConsoleObserver* console);
ConsoleObserver* create_console_observer(Monitor** monitors, int count);

#endif // CONSOLE_OBSERVER_H