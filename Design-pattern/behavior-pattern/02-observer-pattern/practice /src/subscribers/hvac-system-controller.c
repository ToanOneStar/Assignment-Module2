#include <stdio.h>
#include <string.h>
#include "hvac-system-controller.h"

void hvacSystemUpdate(Subscriber* self, Publisher* context, const char* eventInfo) {
    (void)self;
    (void)context;

    if (strcmp(eventInfo, "Temperature is over 35 degrees celsius") == 0) {
        printf("[HvacSystem] alert: %s - HVAC System is opend\n", eventInfo);
    }

    if (strcmp(eventInfo, "Smoke Detected") == 0) {
        printf("[HvacSystem] alert: %s - HVAC System is opened\n", eventInfo);
    }
}

void hvacSystemControllerInit(HvacSystemController* controller) {
    controller->base.update = hvacSystemUpdate;
    controller->base.data = NULL;
}