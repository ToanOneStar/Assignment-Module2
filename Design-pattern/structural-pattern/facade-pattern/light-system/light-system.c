#include <stdio.h>
#include <stdlib.h>
#include "light-system.h"

static void turnOnLightSystem(void) {
    printf("The lighting system is on\n");
}

static void turnOffLightSystem(void) {
    printf("The lighting system is off\n");
}

static void setBrightness(int value) {
    if (value < 0 || value > 100) {
        printf("Value brightness must be between 0 and 100%%\n");
        return;
    }

    printf("Brightness is %d%%\n", value);
}

LightSystem* createLightSystem() {
    LightSystem* system = (LightSystem*)malloc(sizeof(LightSystem));

    system->turnOnLightSystem = turnOnLightSystem;
    system->turnOffLightSystem = turnOffLightSystem;
    system->setBrightness = setBrightness;

    return system;
}