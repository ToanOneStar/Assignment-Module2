#include "monitoring-system.h"
#include "factory.h"

MonitoringSystem* create_monitoring_system() {
    MonitoringSystem* system = malloc(sizeof(MonitoringSystem));

    system->config = load_config("monitoring.conf");

    system->monitors[0] = factory.create_monitor(MONITOR_CPU);
    system->monitors[1] = factory.create_monitor(MONITOR_MEMORY);
    system->monitors[2] = factory.create_monitor(MONITOR_STORAGE);
    system->monitors[3] = factory.create_monitor(MONITOR_NETWORK);
    system->monitors[4] = factory.create_monitor(MONITOR_SYSTEM);

    system->console = create_console_observer(system->monitors, 5);
    system->logger = create_logger_observer(system->config->log_file);
    system->api = create_api_observer(system->config->api_port);

    for (int i = 0; i < 5; i++) {
        system->monitors[i]->subject->attach(system->monitors[i]->subject, (Observer*)system->console);
        system->monitors[i]->subject->attach(system->monitors[i]->subject, (Observer*)system->logger);
        system->monitors[i]->subject->attach(system->monitors[i]->subject, (Observer*)system->api);
    }

    system->running = 0;

    printf("Monitoring System initialized successfully!\n");
    return system;
}

void start_monitoring_system(MonitoringSystem* system) {
    system->running = 1;

    for (int i = 0; i < 5; i++) {
        system->monitors[i]->start(system->monitors[i]);
    }

    printf("\nMonitoring System Started!\n");
    printf("Press 'q' to quit, 'c' to save config, 'r' to reload config\n\n");

    while (system->running) {
        display_monitoring_data(system->console);

        fd_set readfds;
        struct timeval timeout;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        timeout.tv_sec = REFRESH_INTERVAL;
        timeout.tv_usec = 0;

        if (select(1, &readfds, NULL, NULL, &timeout) > 0) {
            char input = getchar();
            switch (input) {
                case 'q':
                case 'Q': system->running = 0; break;
                case 'c':
                case 'C': save_config(system->config, "monitoring.conf"); break;
                case 'r':
                case 'R':
                    free(system->config);
                    system->config = load_config("monitoring.conf");
                    break;
            }
        }
    }
}

void stop_monitoring_system(MonitoringSystem* system) {
    system->running = 0;

    for (int i = 0; i < 5; i++) {
        system->monitors[i]->stop(system->monitors[i]);
    }

    printf("\nMonitoring System Stopped!\n");
}

void cleanup_monitoring_system(MonitoringSystem* system) {
    for (int i = 0; i < 5; i++) {
        free(system->monitors[i]->subject);
        free(system->monitors[i]);
    }

    cleanup_logger_observer(system->logger);
    cleanup_api_observer(system->api);
    free(system->console);
    free(system->config);
    free(system);

    printf("System resources cleaned up.\n");
}