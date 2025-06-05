#ifndef ALARM_SYSTEM_CONTROLLER_H
#define ALARM_SYSTEM_CONTROLLER_H

#include "../subscriber.h"

typedef struct {
    Subscriber base;
} AlarmSystemController;

void alarmSystemControllerInit(AlarmSystemController* controller);

#endif // ALARM_SYSTEM_CONTROLLER_H
