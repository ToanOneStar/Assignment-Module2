#include <stdio.h>
#include <stdlib.h>
#include "music-player.h"

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

static void changeState(MusicPlayer* player, PlayerState* newState) {
    if (player->currentState) {
        free(player->currentState);
    }

    player->currentState = newState;
    if (player->currentState != NULL && player->currentState->setContext != NULL) {
        player->currentState->setContext(player->currentState, player);
    }
}

MusicPlayer* createMusicPlayer(PlayerState* initialState) {
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

void destroyMusicPlayer(MusicPlayer* player) {
    if (player) {
        if (player->currentState) {
            free(player->currentState);
        }

        free(player);
    }
}