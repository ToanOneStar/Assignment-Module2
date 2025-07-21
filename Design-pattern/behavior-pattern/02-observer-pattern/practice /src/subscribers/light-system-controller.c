#include <stdio.h>
#include <string.h>
#include "light-system-controller.h"

void lightSystemUpdate(Subscriber* self, Publisher* context, const char* eventInfo) {
    (void)self;
    (void)context;

    if (strcmp(eventInfo, "Motion is detected in the living room") == 0) {
        printf("[LightSystem] alert: %s - light system is on\n", eventInfo);
    }
}

void lightSystemControllerInit(LightSystemController* controller) {
    controller->base.update = lightSystemUpdate;
    controller->base.data = NULL;
}