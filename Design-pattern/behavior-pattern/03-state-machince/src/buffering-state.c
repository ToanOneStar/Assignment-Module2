#include <stdio.h>
#include <stdlib.h>
#include "buffering-state.h"
#include "error-state.h"
#include "playing-state.h"
#include "stopped-state.h"

static void pressPlay(PlayerState* state);
static void pressPause(PlayerState* state);
static void pressStop(PlayerState* state);
static void setContext(PlayerState* state, struct MusicPlayer* player);

static void pressPlay(PlayerState* state) {
    printf("Buffering...Can not press play button\n");
}

static void pressPause(PlayerState* state) {
    printf("Buffering...Can not press pause button\n");
}

static void pressStop(PlayerState* state) {

    printf("Buffer is canceled -> next to Stopped State\n");
    state->player->changeState(state->player, createStoppedState());
}

static void setContext(PlayerState* state, MusicPlayer* player) {
    state->player = player;
    printf("Current State: Buffering...\n");
}

PlayerState* createBufferingState(void) {
    PlayerState* state = (PlayerState*)malloc(sizeof(PlayerState));

    state->pressPlay = pressPlay;
    state->pressPause = pressPause;
    state->pressStop = pressStop;
    state->setContext = setContext;
    state->player = NULL;

    return (PlayerState*)state;
}

void bufferingComplete(PlayerState* state) {
    printf("Buffering success -> Playing\n");
    state->player->changeState(state->player, createPlayingState());
}

void bufferingError(PlayerState* state) {
    printf("Buffering fail -> next to error state\n");
    state->player->changeState(state->player, createErrorState());
}