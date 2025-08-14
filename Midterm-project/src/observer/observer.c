#include "observer.h"

/**
 * @brief Attach an observer to the subject.
 * 
 * Adds the specified observer to the subject's list of observers if
 * there is space available. Attached observers will receive updates
 * when the subject notifies them.
 * 
 * @param self (in) Pointer to the Subject to attach the observer to.
 * @param observer (in) Pointer to the Observer to attach.
 * 
 * @return void Does not return a value.
 * 
 * @note The maximum number of observers is limited by MAX_OBSERVERS.
 */
void subject_attach(Subject* self, Observer* observer) {
    if (self->observer_count < MAX_OBSERVERS) {
        self->observers[self->observer_count++] = observer;
        printf("Observer '%s' attached\n", observer->name);
    }
}

/**
 * @brief Detach an observer from the subject.
 * 
 * Removes the specified observer from the subject's list of observers.
 * If the observer is found, it is removed and the observer list is
 * compacted to fill the gap.
 * 
 * @param self (in) Pointer to the Subject from which the observer will be detached.
 * @param observer (in) Pointer to the Observer to detach.
 * 
 * @return void Does not return a value.
 * 
 * @note Prints a message indicating which observer was detached.
 */
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

/**
 * @brief Notify all attached observers with new data.
 * 
 * Iterates through the list of observers attached to the subject and calls
 * each observer's update method, passing the subject and the provided data.
 * This implements the notification mechanism in the Observer pattern.
 * 
 * @param self (in) Pointer to the Subject sending the notification.
 * @param data (in) Pointer to the data to send to observers (e.g., AlertData).
 * 
 * @return void Does not return a value.
 */
void subject_notify(Subject* self, void* data) {
    for (int i = 0; i < self->observer_count; i++) {
        self->observers[i]->update(self->observers[i], self, data);
    }
}

/**
 * @brief Create and initialize a new Subject instance.
 * 
 * Allocates memory for a Subject, initializes the observer count to zero,
 * and sets the function pointers for attaching, detaching, and notifying
 * observers. This prepares the Subject for use in the Observer pattern.
 * 
 * @return Subject* Pointer to the newly created Subject.
 */
Subject* create_subject() {
    Subject* subject = (Subject*)malloc(sizeof(Subject));

    subject->observer_count = 0;
    subject->attach = subject_attach;
    subject->detach = subject_detach;
    subject->notify = subject_notify;

    return subject;
}