#ifndef OBSERVER_H
#define OBSERVER_H

#include "common.h"

typedef struct Observer Observer;
typedef struct Subject Subject;

struct Observer {
    void (*update)(Observer* self, Subject* subject, void* data);
    char name[MAX_STRING_LEN];
};

struct Subject {
    Observer* observers[MAX_OBSERVERS];
    int observer_count;
    void (*attach)(Subject* self, Observer* observer);
    void (*detach)(Subject* self, Observer* observer);
    void (*notify)(Subject* self, void* data);
};

Subject* create_subject();
void subject_attach(Subject* self, Observer* observer);
void subject_detach(Subject* self, Observer* observer);
void subject_notify(Subject* self, void* data);

#endif // OBSERVER_H