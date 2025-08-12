#include "observer.h"

void subject_attach(Subject* self, Observer* observer) {
    if (self->observer_count < MAX_OBSERVERS) {
        self->observers[self->observer_count++] = observer;
        printf("Observer '%s' attached\n", observer->name);
    }
}

void subject_detach(Subject* self, Observer* observer) {
    for (int i = 0; i < self->observer_count; i++) {
        if (self->observers[i] == observer) {
            for (int j = i; j < self->observer_count - 1; j++) {
                self->observers[j] = self->observers[j + 1];
            }
            
            self->observer_count--;
            printf("Observer '%s' detached\n", observer->name);
            break;
        }
    }
}

void subject_notify(Subject* self, void* data) {
    for (int i = 0; i < self->observer_count; i++) {
        self->observers[i]->update(self->observers[i], self, data);
    }
}

Subject* create_subject() {
    Subject* subject = (Subject*)malloc(sizeof(Subject));

    subject->observer_count = 0;
    subject->attach = subject_attach;
    subject->detach = subject_detach;
    subject->notify = subject_notify;

    return subject;
}