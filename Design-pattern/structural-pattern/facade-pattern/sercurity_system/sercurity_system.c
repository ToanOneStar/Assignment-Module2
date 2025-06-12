#include <stdio.h>
#include <stdlib.h>
#include "sercurity_system.h"

static void activeAlarm(void) {
    printf("Actived alarm!\n");
}

static void deactiveAlarm(void) {
    printf("Deactived alarm!\n");
}

static void monitorSensor(void) {
    printf("Monitoring sensor\n");
}

SercuritySystem* createSercuritySystem(void) {
    SercuritySystem* system = (SercuritySystem*)malloc(sizeof(SercuritySystem));
    /*assign funtions of sercurity system*/
    system->activeAlarm = activeAlarm;
    system->deactiveAlarm = deactiveAlarm;
    system->monitorSensor = monitorSensor;
    return system;
}