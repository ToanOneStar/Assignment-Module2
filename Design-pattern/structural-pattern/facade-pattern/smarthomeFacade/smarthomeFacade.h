#ifndef SMART_HOME_FACADE_H
#define SMART_HOME_FACADE_H

#include "../hvac_system/hvac_system.h"
#include "../light_system/light_system.h"
#include "../sercurity_system/sercurity_system.h"

typedef struct SmartHomeFacade {
    LightSystem* lightSystem;
    HvacSystem* hvacSystem;
    SercuritySystem* sercuritySystem;
} SmartHomeFacade;

/*function to create a new smart home facade*/
SmartHomeFacade* createSmartHomeFacade(void);

/*user scenarios*/
void activateMorningRoutine(SmartHomeFacade* facade);
void activateAwayMode(SmartHomeFacade* facade);
void setMovieNightScene(SmartHomeFacade* facade);
#endif