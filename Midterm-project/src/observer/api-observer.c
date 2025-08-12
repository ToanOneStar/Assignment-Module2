#include "api-observer.h"

void api_update(Observer* self, Subject* subject, void* data) {
    APIObserver* api = (APIObserver*)self;
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

void* api_server_thread(void* arg) {
    APIObserver* api = (APIObserver*)arg;

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

APIObserver* create_api_observer(int port) {
    APIObserver* api = malloc(sizeof(APIObserver));

    strcpy(api->base.name, "APIServer");
    api->base.update = api_update;
    api->port = port;
    api->latest_data = NULL;
    pthread_create(&api->server_thread, NULL, api_server_thread, api);

    return api;
}

void cleanup_api_observer(APIObserver* api) {
    if (api->latest_data) {
        free(api->latest_data);
    }
    free(api);
}