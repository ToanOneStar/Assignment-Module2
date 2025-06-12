#ifndef HVAC_SYSTEM_CONTROLLER_H
#define HVAC_SYSTEM_CONTROLLER_H

#include "../subscriber.h"

typedef struct {
    Subscriber base;
} HAVCSystemController;

void hvacSystemControllerInit(HAVCSystemController* controller);

#endif // HVAC_SYSTEM_CONTROLLER_H 