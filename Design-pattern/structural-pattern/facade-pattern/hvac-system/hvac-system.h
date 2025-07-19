#ifndef HVAC_SYSTEM_H
#define HVAC_SYSTEM_H

typedef struct {
    void (*setTemperature)(int value);
    void (*setMode)(const char* mode);
} HvacSystem;

HvacSystem* createHvacSystem(void);

#endif // HVAC_SYSTEM_H