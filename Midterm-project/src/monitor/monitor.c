#include "monitor.h"

/**
 * @brief Thread function to periodically collect monitor data.
 * 
 * Continuously calls the monitor's collect_data function at intervals defined
 * by REFRESH_INTERVAL while the monitor is running.
 * 
 * @param arg (in) Pointer to Monitor instance.
 * 
 * @return NULL
 */
void* monitor_thread(void* arg) {
    Monitor* monitor = (Monitor*)arg;
    
    while (monitor->running) {
        monitor->collect_data(monitor);
        sleep(REFRESH_INTERVAL);
    }
    
    return NULL;
}

/**
 * @brief Start the monitor by launching its data collection thread.
 * 
 * Sets the running flag to true and creates a new thread to execute monitor_thread.
 * 
 * @param self (in) Pointer to Monitor instance to start.
 * 
 * @return void
 */
void monitor_start(Monitor* self) {
    self->running = 1;
    pthread_create(&self->thread, NULL, monitor_thread, self);
}

/**
 * @brief Stop the monitor and wait for its thread to finish.
 * 
 * Sets the running flag to false and joins the monitor's data collection thread
 * to ensure it has terminated.
 * 
 * @param self (in) Pointer to Monitor instance to stop.
 * 
 * @return void
 */
void monitor_stop(Monitor* self) {
    self->running = 0;
    pthread_join(self->thread, NULL);
}