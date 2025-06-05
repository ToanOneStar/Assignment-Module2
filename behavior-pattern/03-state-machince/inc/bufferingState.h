#ifndef BUFFERING_STATE_H
#define BUFFERING_STATE_H

#include "musicPlayer.h"
#include "playerState.h"

PlayerState* bufferingStateCreate(void);

/*Functions simulate result buffer*/
void bufferingComplete(PlayerState* state);
void bufferingError(PlayerState* state);

#endif