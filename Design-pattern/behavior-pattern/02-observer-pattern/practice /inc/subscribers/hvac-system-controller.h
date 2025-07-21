#ifndef HVAC_SYSTEM_CONTROLLER_H
#define HVAC_SYSTEM_CONTROLLER_H

#include "subscriber.h"

typedef struct {
    Subscriber base;
} HvacSystemController;

void hvacSystemControllerInit(HvacSystemController* controller);

#endif // HVAC_SYSTEM_CONTROLLER_H