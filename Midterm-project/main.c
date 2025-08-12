#include "common.h"
#include "monitoring-system.h"

MonitoringSystem* global_system = NULL;

void signal_handler(int sig) {
    if (global_system) {
        printf("\n\nReceived signal %d, shutting down gracefully...\n", sig);
        stop_monitoring_system(global_system);
        cleanup_monitoring_system(global_system);
        exit(0);
    }
}

int main(int argc, char* argv[]) {
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                    EMBEDDED MONITORING SYSTEM v1.0                          ║\n");
    printf("║                    Design Patterns: Factory + Observer                      ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n\n");

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    global_system = create_monitoring_system();
    start_monitoring_system(global_system);

    stop_monitoring_system(global_system);
    cleanup_monitoring_system(global_system);

    printf("\nEmbedded Monitoring System shutdown complete.\n");
    printf("Thank you for using our monitoring solution!\n");

    return 0;
}