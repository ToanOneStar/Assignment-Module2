#ifndef SMART_HOME_h
#define SMART_HOME_H

#include "hvac-system.h"
#include "light-system.h"
#include "sercurity-system.h"

typedef struct SmartHomeFacade {
    LightSystem* lightSystem;
    HvacSystem* hvacSystem;
    SercuritySystem* sercuritySystem;
} SmartHomeFacade;

SmartHomeFacade* createSmartHomeFacade(void);

void activateMorningRoutine(SmartHomeFacade* facade);
void activateAwayMode(SmartHomeFacade* facade);
void setMovieNightMode(SmartHomeFacade* facade);

#endif // SMART_HOME_H