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

PlayerState* playingStateCreate() {
    PlayerState* state = (PlayerState*)malloc(sizeof(PlayerState));
    state->pressPlay = pressPlay;
    state->pressPause = pressPause;
    state->pressStop = pressStop;
    state->setContext = setContext;
    state->player = NULL;
    return state;
}

static void pressPlay(PlayerState* state) {
    printf("Music is already playing.\n");
}

static void pressPause(PlayerState* state) {
    printf("Pausing music...\n");
    state->player->changeState(state->player, pausedStateCreate());
}

static void pressStop(PlayerState* state) {
    printf("Stopping music...\n");
    state->player->changeState(state->player, stoppedStateCreate());
}

static void setContext(PlayerState* state, struct MusicPlayer* player) {
    state->player = player;
}
