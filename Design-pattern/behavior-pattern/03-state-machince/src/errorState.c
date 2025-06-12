#include <stdio.h>
#include <stdlib.h>
#include "../inc/bufferingState.h"
#include "../inc/errorState.h"
#include "../inc/musicPlayer.h"
#include "../inc/pausedState.h"
#include "../inc/playingState.h"
#include "../inc/stoppedState.h"

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
    state->player->changeState(state->player, stoppedStateCreate());
}

static void setContext(PlayerState* state, MusicPlayer* player) {
    state->player = player;
    printf("Error...\n");
}

PlayerState* errorStateCreate(void) {
    PlayerState* state = (PlayerState*)malloc(sizeof(PlayerState));
    state->pressPlay = pressPlay;
    state->pressPause = pressPause;
    state->pressStop = pressStop;
    state->setContext = setContext;
    state->player = NULL;

    return (PlayerState*)state;
}