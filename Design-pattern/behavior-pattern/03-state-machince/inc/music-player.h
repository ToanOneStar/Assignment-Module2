#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "player-state.h"

typedef struct MusicPlayer {
    PlayerState* currentState;
    void (*changeState)(struct MusicPlayer* player, PlayerState* newState);
    void (*clickPlayButton)(struct MusicPlayer* player);
    void (*clickPauseButton)(struct MusicPlayer* player);
    void (*clickStopButton)(struct MusicPlayer* player);
} MusicPlayer;

MusicPlayer* createMusicPlayer(PlayerState* initialState);

void destroyMusicPlayer(MusicPlayer* player);

#endif // MUSIC_PLAYER_H