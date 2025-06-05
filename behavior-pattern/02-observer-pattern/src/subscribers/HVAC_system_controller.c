#include <stdio.h>
#include <string.h>
#include "../../inc/subscribers/HVAC_system_controller.h"

// Update method for HVAC System Controller
void hvacSystemUpdate(Subscriber* self, Publisher* context, const char* eventInfo) {
    (void)self;
    (void)context;
    if (strcmp(eventInfo, "Temperature is over 35 degrees celsius") == 0) {
        printf("[HVACSystem] alert: %s - HAVC System is opend\n", eventInfo);
    }
    if (strcmp(eventInfo, "Smoke Detected") == 0) {
        printf("[HVACSystem] alert: %s - HAVC System is opend\n", eventInfo);
    }
}

// Initialize HVAC System Controller
void hvacSystemControllerInit(HAVCSystemController* controller) {
    controller->base.update = hvacSystemUpdate;
    controller->base.data = NULL;
}
