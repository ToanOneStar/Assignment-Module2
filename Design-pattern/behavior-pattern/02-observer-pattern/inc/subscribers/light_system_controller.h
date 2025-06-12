#ifndef LIGHT_SYSTEM_CONTROLLER_H
#define LIGHT_SYSTEM_CONTROLLER_H

#include "../subscriber.h"

typedef struct {
    Subscriber base;
} LightSystemController;

void lightSystemControllerInit(LightSystemController* controller);

#endif // LIGHT_SYSTEM_CONTROLLER_H