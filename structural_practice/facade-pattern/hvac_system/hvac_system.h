#ifndef HVAC_SYSTEM_H
#define HVAC_SYSTEM_H

typedef struct {
    void (*setTemperature)(int value); 
    void (*setMode)(const char* mode); 
} HvacSystem;

/*function to create a new hvac system*/
HvacSystem* createHvacSystem(void);

#endif