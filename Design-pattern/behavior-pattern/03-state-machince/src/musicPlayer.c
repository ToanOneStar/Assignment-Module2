#include <stdio.h>
#include <stdlib.h>
#include "../inc/musicPlayer.h"

// Button event implementations
static void clickPlayButton(MusicPlayer* player) {
    if (player->currentState && player->currentState->pressPlay) {
        player->currentState->pressPlay(player->currentState);
    }
}

static void clickPauseButton(MusicPlayer* player) {
    if (player->currentState && player->currentState->pressPause) {
        player->currentState->pressPause(player->currentState);
    }
}

static void clickStopButton(MusicPlayer* player) {
    if (player->currentState && player->currentState->pressStop) {
        player->currentState->pressStop(player->currentState);
    }
}

// Change state implementation
static void changeState(MusicPlayer* player, PlayerState* newState) {
    if (player->currentState) {
        free(player->currentState); // Free old state
    }
    player->currentState = newState;
    if (player->currentState && player->currentState->setContext) {
        player->currentState->setContext(player->currentState, player);
    }
}

// Constructor
MusicPlayer* musicPlayerCreate(PlayerState* initialState) {
    MusicPlayer* player = (MusicPlayer*)malloc(sizeof(MusicPlayer));
    player->currentState = initialState;
    player->changeState = changeState;
    player->clickPlayButton = clickPlayButton;
    player->clickPauseButton = clickPauseButton;
    player->clickStopButton = clickStopButton;
    if (initialState && initialState->setContext) {
        initialState->setContext(initialState, player);
    }
    return player;
}

// Destructor
void musicPlayerDestroy(MusicPlayer* player) {
    if (player) {
        if (player->currentState) {
            free(player->currentState);
        }
        free(player);
    }
}
