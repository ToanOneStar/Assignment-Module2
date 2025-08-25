#include "logger.h"

#define USER_ID 12345
const char* USERNAME = "admin";

int main() {
    printf("=== DEMO LOGGER ===\n\n");

    log_message(LOG_INFO, "Start program");
    log_message(LOG_DEBUG, "Init system...");
    log_message(LOG_WARNING, "Warning !!!");
    log_message(LOG_ERROR, "Error: Can not connect to Internet");
    log_message(LOG_CRITICAL, "Serious: System is unstable.");

    // Demo format string
    log_message(LOG_INFO, "User %s (ID: %d) logged in", USERNAME, USER_ID);
    log_message(LOG_ALERT, "ALERT: Disk space low");
    log_message(LOG_INFO, "End Program");

    printf("\nCheck file 'log.txt' to view the log that has been recorded.\n");
    return 0;
}