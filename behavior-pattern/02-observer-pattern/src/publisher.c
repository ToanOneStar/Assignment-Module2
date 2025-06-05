#include "../inc/publisher.h"
#include <string.h>

// Subscribe a subscriber to the publisher
void publisherSubscribe(Publisher* self, Subscriber* s) {
    if (self->subscriberCount < MAX_SUBSCRIBERS) {
        self->subscribers[self->subscriberCount++] = s;
    }
}

// Unsubscribe a subscriber from the publisher
void publisherUnsubscribe(Publisher* self, Subscriber* s) {
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

// Notify all subscribers about an event
void publisherNotifySubscribers(Publisher* self, const char* eventInfo) {
    for (int i = 0; i < self->subscriberCount; ++i) {
        if (self->subscribers[i] && self->subscribers[i]->update) {
            self->subscribers[i]->update(self->subscribers[i], self, eventInfo);
        }
    }
}

// Initialize the publisher struct
void publisherInit(Publisher* pub) {
    memset(pub, 0, sizeof(Publisher));
    pub->subscribe = publisherSubscribe;
    pub->unsubscribe = publisherUnsubscribe;
    pub->notifySubscribers = publisherNotifySubscribers;
}