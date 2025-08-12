#include "monitor.h"

void* monitor_thread(void* arg) {
    Monitor* monitor = (Monitor*)arg;
    
    while (monitor->running) {
        monitor->collect_data(monitor);
        sleep(REFRESH_INTERVAL);
    }
    
    return NULL;
}

void monitor_start(Monitor* self) {
    self->running = 1;
    pthread_create(&self->thread, NULL, monitor_thread, self);
}

void monitor_stop(Monitor* self) {
    self->running = 0;
    pthread_join(self->thread, NULL);
}