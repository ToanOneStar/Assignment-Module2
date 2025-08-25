#ifndef LIGHT_SYSTEM_H
#define LIGHT_SYSTEM_H

typedef struct {
    void (*turnOnLightSystem)(void);
    void (*turnOffLightSystem)(void);
    void (*setBrightness)(int value);
} LightSystem;

LightSystem* createLightSystem(void);

#endif // LIGHT_SYSTEM_H