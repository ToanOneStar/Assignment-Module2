#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "playerState.h"

// Context
typedef struct MusicPlayer {
    PlayerState *currentState;
    void (*changeState)(struct MusicPlayer *player, PlayerState *newState);

    // Button events
    void (*clickPlayButton)(struct MusicPlayer *player);
    void (*clickPauseButton)(struct MusicPlayer *player);
    void (*clickStopButton)(struct MusicPlayer *player);
} MusicPlayer;

// Constructor
MusicPlayer* musicPlayerCreate(PlayerState *initialState);
// Destructor
void musicPlayerDestroy(MusicPlayer *player);

#endif
