#ifndef SERCURITY_SYSTEM_H
#define SERCURITY_SYSTEM_H

typedef struct {
    void (*activeAlarm)(void);
    void (*deactiveAlarm)(void);
    void (*monitorSensor)(void);
} SercuritySystem;

SercuritySystem* createSercuritySystem(void);

#endif // SERCURITY_SYSTEM_H