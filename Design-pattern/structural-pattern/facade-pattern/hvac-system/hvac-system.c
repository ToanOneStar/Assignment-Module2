#include <stdio.h>
#include <stdlib.h>
#include "hvac-system.h"

static void setTemperature(int value) {
    printf("Room temperature is %d\n", value);
}

static void setMode(const char* mode) {
    printf("Current mode is %s\n", mode);
}

HvacSystem* createHvacSystem(void) {
    HvacSystem* system = (HvacSystem*)malloc(sizeof(HvacSystem));
    system->setTemperature = setTemperature;
    system->setMode = setMode;

    return system;
}