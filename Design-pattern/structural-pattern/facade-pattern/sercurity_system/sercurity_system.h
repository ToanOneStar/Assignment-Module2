#ifndef SERCURITY_SYSTEM_H
#define SERCURITY_SYSTEM_H

typedef struct {
    void (*activeAlarm)(void);
    void (*deactiveAlarm)(void);
    void (*monitorSensor)(void);
} SercuritySystem;

/*function to create a new sercurity system*/
SercuritySystem* createSercuritySystem(void);

#endif