#include <stdio.h>
#include <stdlib.h>
#include "smart-home.h"

#define BRIGHTNESS_OF_MORNING_ROUTINE_MODE    100
#define BRIGHTNESS_OF_MOVIE_NIGHT_SCENE_MODE  21
#define TEMPERATURE_OF_MORNING_ROUTINE_MODE   25
#define TEMPERATURE_OF_AWAY_MODE              26
#define TEMPERATURE_OF_MOVIE_NIGHT_SCENE_MODE 21
#define COOL_MODE                             "Cooling"
#define ECO_MODE                              "Eco"

SmartHomeFacade* createSmartHomeFacade(void) {
    SmartHomeFacade* facade = (SmartHomeFacade*)malloc(sizeof(SmartHomeFacade));

    facade->lightSystem = createLightSystem();
    facade->hvacSystem = createHvacSystem();
    facade->sercuritySystem = createSercuritySystem();

    return facade;
}

void activateMorningRoutine(SmartHomeFacade* facade) {
    facade->lightSystem->turnOffLightSystem();
    facade->lightSystem->setBrightness(BRIGHTNESS_OF_MORNING_ROUTINE_MODE);
    facade->hvacSystem->setTemperature(TEMPERATURE_OF_MORNING_ROUTINE_MODE);
    facade->hvacSystem->setMode(COOL_MODE);
    facade->sercuritySystem->deactiveAlarm();

    printf("Morning routine actived\n");
}

void activateAwayMode(SmartHomeFacade* facade) {
    facade->lightSystem->turnOffLightSystem();
    facade->sercuritySystem->activeAlarm();
    facade->hvacSystem->setTemperature(TEMPERATURE_OF_AWAY_MODE);
    facade->hvacSystem->setMode(ECO_MODE);

    printf("Away mode activated.\n");
}

void setMovieNightScene(SmartHomeFacade* facade) {
    facade->lightSystem->setBrightness(BRIGHTNESS_OF_MOVIE_NIGHT_SCENE_MODE);
    facade->hvacSystem->setTemperature(TEMPERATURE_OF_MOVIE_NIGHT_SCENE_MODE);
    facade->sercuritySystem->deactiveAlarm();

    printf("Movie night scene set.\n");
}