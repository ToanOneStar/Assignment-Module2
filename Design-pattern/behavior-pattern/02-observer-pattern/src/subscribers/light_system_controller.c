#include <stdio.h>
#include <string.h>
#include "../../inc/subscribers/light_system_controller.h"

// Update method for Light System Controller
void lightSystemUpdate(Subscriber* self, Publisher* context, const char* eventInfo) {
    (void)self;
    (void)context;
    if (strcmp(eventInfo, "Motion is detected in the living room") == 0) {
        printf("[LightSystem] alert: %s - light system is on\n", eventInfo);
    }
}

// Initialize Light System Controller
void lightSystemControllerInit(LightSystemController* controller) {
    controller->base.update = lightSystemUpdate;
    controller->base.data = NULL;
}
