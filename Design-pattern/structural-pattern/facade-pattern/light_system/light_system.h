#ifndef LIGHT_SYSTEM_H
#define LIGHT_SYSTEM_H

typedef struct {
    void (*turnOn)(void);
    void (*turnOff)(void);
    void (*setBrightness)(int value);
} LightSystem;

/*function to create a new light system*/
LightSystem* createLightSystem(void);

#endif