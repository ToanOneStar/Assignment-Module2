#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

typedef struct Publisher Publisher;

// Subscriber interface
typedef struct Subscriber {
    void (*update)(struct Subscriber* self, Publisher* context, const char* eventInfo);
    void* data;
} Subscriber;

#endif // SUBSCRIBER_H
