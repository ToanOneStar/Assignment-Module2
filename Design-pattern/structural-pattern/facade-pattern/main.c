#include <stdio.h>
#include <stdlib.h>
#include "smarthomeFacade/smarthomeFacade.h"

int main() {
    SmartHomeFacade* smartHome = createSmartHomeFacade();

    printf(">>> Activating morning routine...\n");
    activateMorningRoutine(smartHome);

    printf("\n>>> Activating away mode...\n");
    activateAwayMode(smartHome);

    printf("\n>>> Setting movie night scene...\n");
    setMovieNightScene(smartHome);

    printf("\nFreeing allocated memory...\n");
    free(smartHome->lightSystem);
    free(smartHome->sercuritySystem);
    free(smartHome->hvacSystem);
    free(smartHome);
}