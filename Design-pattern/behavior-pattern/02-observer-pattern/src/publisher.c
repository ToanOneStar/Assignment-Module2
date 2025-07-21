#include <string.h>
#include "publisher.h"

void subscribePublisher(Publisher* self, Subscriber* s) {
    if (self->subscriberCount < MAX_SUBSCRIBERS) {
        self->subscribers[self->subscriberCount++] = s;
    }
}

void unsubcribePublisher(Publisher* self, Subscriber* s) {
    for (int i = 0; i < self->subscriberCount; ++i) {
        if (self->subscribers[i] == s) {
            for (int j = i; j < self->subscriberCount - 1; ++j) {
                self->subscribers[j] = self->subscribers[j + 1];
            }

            self->subscriberCount--;
            break;
        }
    }
}

void notifySubscribers(Publisher* self, const char* eventInfo) {
    for (int i = 0; i < self->subscriberCount; ++i) {
        if (self->subscribers[i] && self->subscribers[i]->update) {
            self->subscribers[i]->update(self->subscribers[i], self, eventInfo);
        }
    }
}

void publisherInit(Publisher* pub) {
    memset(pub, 0, sizeof(Publisher));
    pub->subscribe = subscribePublisher;
    pub->unsubscribe = unsubcribePublisher;
    pub->notifySubscribers = notifySubscribers;
}