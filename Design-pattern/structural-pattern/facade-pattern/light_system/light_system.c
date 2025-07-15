#include <stdio.h>
#include <stdlib.h>
#include "light_system.h"

static void turnOn(void) {
    printf("The lighting system is on.\n");
}

static void turnOff(void) {
    printf("The lighting system is off\n");
}

static void setBrightness(int value) {
    printf("Brightness is %d%%\n", value);
}

LightSystem* createLightSystem() {
    LightSystem* system = (LightSystem*)malloc(sizeof(LightSystem));

    system->turnOn = turnOn;
    system->turnOff = turnOff;
    system->setBrightness = setBrightness;

    return system;
}
