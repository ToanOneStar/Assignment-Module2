#ifndef BUFFERING_STATE_H
#define BUFFERING_STATE_H

#include "music-player.h"
#include "player-state.h"

PlayerState* createBufferingState(void);

void bufferingComplete(PlayerState* state);
void bufferingError(PlayerState* state);

#endif // BUFFERING_STATE_H