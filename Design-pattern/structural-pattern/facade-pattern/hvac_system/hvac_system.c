#include <stdio.h>
#include <stdlib.h>
#include "hvac_system.h"

static void setTemperature(int value) {
    printf("Room temperature is %d\n", value);
}

static void setMode(const char* mode) {
    printf("Current mode is %s", mode);
}

HvacSystem* createHvacSystem(void) {
    HvacSystem* system = (HvacSystem*)malloc(sizeof(HvacSystem));
    /*assign funtions of hvac system*/
    system->setTemperature = setTemperature;
    system->setMode = setMode;
    return system;
}