#ifndef API_OBSERVER_H
#define API_OBSERVER_H
#include "observer.h"

typedef struct {
    Observer base;
    int port;
    char* latest_data;
    pthread_t server_thread;
} APIObserver;

APIObserver* create_api_observer(int port);

void api_update(Observer* self, Subject* subject, void* data);
void* api_server_thread(void* arg);
void cleanup_api_observer(APIObserver* api);

#endif // API_OBSERVER_H