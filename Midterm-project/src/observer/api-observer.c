#include "api-observer.h"

/**
 * @brief Update the API observer with new alert data.
 * 
 * Receives alert data from the subject, formats it as a JSON string,
 * and stores it in the ApiObserver's latest_data field, freeing previous data if any.
 * 
 * @param self (in) Pointer to Observer, cast to ApiObserver inside the function.
 * @param subject (in) Pointer to Subject sending the update.
 * @param data (in) Pointer to AlertData containing the alert information.
 * 
 * @return void
 */
void api_update(Observer* self, Subject* subject, void* data) {
    ApiObserver* api = (ApiObserver*)self;
    AlertData* alert = (AlertData*)data;

    if (alert) {
        if (api->latest_data) {
            free(api->latest_data);
        }

        api->latest_data = malloc(MAX_STRING_LEN);
        snprintf(api->latest_data,
                 MAX_STRING_LEN,
                 "{\"alert\": {\"level\": %d, \"source\": %d, \"message\": \"%s\", \"timestamp\": %ld}}",
                 alert->level,
                 alert->source,
                 alert->message,
                 alert->timestamp);
    }
}

/**
 * @brief Thread function for the API server.
 * 
 * Prints available endpoints and periodically checks for the latest alert data,
 * simulating an API server that serves system status, alerts, and configuration.
 * 
 * @param arg (in) Pointer to ApiObserver instance.
 * 
 * @return NULL
 */
void* api_server_thread(void* arg) {
    ApiObserver* api = (ApiObserver*)arg;

    printf("API Server listening on port %d\n", api->port);
    printf("Endpoints available:\n");
    printf("  - GET /status    - System status\n");
    printf("  - GET /alerts    - Latest alerts\n");
    printf("  - GET /config    - Current configuration\n");
    printf("  - POST /config   - Update configuration\n");

    while (1) {
        sleep(10);
        if (api->latest_data) {
            printf("API: Latest alert data available\n");
        }
    }

    return NULL;
}

/**
 * @brief Create and initialize an ApiObserver instance.
 * 
 * Allocates memory for ApiObserver, sets the update callback, initializes
 * the listening port, and starts the API server thread.
 * 
 * @param port (in) Port number for the API server.
 * 
 * @return Pointer to the newly created ApiObserver instance.
 */
ApiObserver* create_api_observer(int port) {
    ApiObserver* api = malloc(sizeof(ApiObserver));

    strcpy(api->base.name, "APIServer");
    api->base.update = api_update;
    api->port = port;
    api->latest_data = NULL;
    pthread_create(&api->server_thread, NULL, api_server_thread, api);

    return api;
}

/**
 * @brief Free resources allocated for an ApiObserver instance.
 * 
 * Frees the latest_data buffer if allocated and then frees the ApiObserver itself.
 * 
 * @param api (in) Pointer to the ApiObserver instance to clean up.
 * 
 * @return void
 */
void cleanup_api_observer(ApiObserver* api) {
    if (api->latest_data) {
        free(api->latest_data);
    }
    free(api);
}