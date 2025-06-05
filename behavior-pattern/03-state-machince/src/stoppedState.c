#include <stdio.h>
#include <stdlib.h>
#include "../inc/musicPlayer.h"
#include "../inc/pausedState.h"
#include "../inc/playingState.h"
#include "../inc/stoppedState.h"

static void pressPlay(PlayerState* state);
static void pressPause(PlayerState* state);
static void pressStop(PlayerState* state);
static void setContext(PlayerState* state, struct MusicPlayer* player);

// Constructor for StoppedState
PlayerState* stoppedStateCreate() {
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
    // Change to PlayingState
    state->player->changeState(state->player, playingStateCreate());
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
