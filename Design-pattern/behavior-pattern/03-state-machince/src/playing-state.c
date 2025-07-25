#include <stdio.h>
#include <stdlib.h>
#include "buffering-state.h"
#include "paused-state.h"
#include "playing-state.h"
#include "stopped-state.h"

static void pressPlay(PlayerState* state);
static void pressPause(PlayerState* state);
static void pressStop(PlayerState* state);
static void setContext(PlayerState* state, struct MusicPlayer* player);

static void pressPlay(PlayerState* state) {
    printf("Music is already playing.\n");
}

static void pressPause(PlayerState* state) {
    printf("Pausing music...\n");
    state->player->changeState(state->player, createPausedState());
}

static void pressStop(PlayerState* state) {
    printf("Stopping music...\n");
    state->player->changeState(state->player, createStoppedState());
}

static void setContext(PlayerState* state, struct MusicPlayer* player) {
    state->player = player;
}

PlayerState* createPlayingState() {
    PlayerState* state = (PlayerState*)malloc(sizeof(PlayerState));

    state->pressPlay = pressPlay;
    state->pressPause = pressPause;
    state->pressStop = pressStop;
    state->setContext = setContext;
    state->player = NULL;

    return state;
}