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

PlayerState* pausedStateCreate() {
    PlayerState* state = (PlayerState*)malloc(sizeof(PlayerState));
    state->pressPlay = pressPlay;
    state->pressPause = pressPause;
    state->pressStop = pressStop;
    state->setContext = setContext;
    state->player = NULL;
    return state;
}

static void pressPlay(PlayerState* state) {
    printf("Resuming music...\n");
    state->player->changeState(state->player, playingStateCreate());
}

static void pressPause(PlayerState* state) {
    printf("Music is already paused.\n");
}

static void pressStop(PlayerState* state) {
    printf("Stopping music from paused state...\n");
    state->player->changeState(state->player, stoppedStateCreate());
}

static void setContext(PlayerState* state, struct MusicPlayer* player) {
    state->player = player;
}
