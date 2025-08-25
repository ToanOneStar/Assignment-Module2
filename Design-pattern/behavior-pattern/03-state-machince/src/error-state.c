#include <stdio.h>
#include <stdlib.h>
#include "error-state.h"
#include "music-player.h"
#include "stopped-state.h"

static void pressPlay(PlayerState* state);
static void pressPause(PlayerState* state);
static void pressStop(PlayerState* state);
static void setContext(PlayerState* state, struct MusicPlayer* player);

static void pressPlay(PlayerState* state) {
    printf("Can not play: currently Error\n");
}

static void pressPause(PlayerState* state) {
    printf("Can not pause: currently Error\n");
}

static void pressStop(PlayerState* state) {
    printf("Stopping from error state...\n");
    state->player->changeState(state->player, createStoppedState());
}

static void setContext(PlayerState* state, MusicPlayer* player) {
    state->player = player;
    printf("Error...\n");
}

PlayerState* createErrorState(void) {
    PlayerState* state = (PlayerState*)malloc(sizeof(PlayerState));

    state->pressPlay = pressPlay;
    state->pressPause = pressPause;
    state->pressStop = pressStop;
    state->setContext = setContext;
    state->player = NULL;

    return (PlayerState*)state;
}