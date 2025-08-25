#include <stdio.h>
#include <stdlib.h>
#include "playing-state.h"
#include "stopped-state.h"

static void pressPlay(PlayerState* state);
static void pressPause(PlayerState* state);
static void pressStop(PlayerState* state);
static void setContext(PlayerState* state, struct MusicPlayer* player);

PlayerState* createStoppedState() {
    PlayerState* state = (PlayerState*)malloc(sizeof(PlayerState));

    state->pressPlay = pressPlay;
    state->pressPause = pressPause;
    state->pressStop = pressStop;
    state->setContext = setContext;
    state->player = NULL;

    return state;
}

static void pressPlay(PlayerState* state) {
    printf("Starting music...\n");
    state->player->changeState(state->player, createPlayingState());
}

static void pressPause(PlayerState* state) {
    printf("Cannot pause. Music is already stopped.\n");
}

static void pressStop(PlayerState* state) {
    printf("Music is already stopped.\n");
}

static void setContext(PlayerState* state, struct MusicPlayer* player) {
    state->player = player;
}