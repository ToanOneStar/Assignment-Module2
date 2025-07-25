#include <stdio.h>
#include "buffering-state.h"
#include "error-state.h"
#include "music-player.h"
#include "paused-state.h"
#include "playing-state.h"
#include "stopped-state.h"

extern void bufferingComplete(PlayerState* state);
extern void bufferingError(PlayerState* state);

int main() {
    MusicPlayer* player = createMusicPlayer(createStoppedState());

    printf("\n[TEST] Current state: Stopped\n");
    player->clickStopButton(player);

    printf("\n[TEST] Press Play -> Transition to Buffering\n");
    player->clickPlayButton(player);

    printf("\n[TEST] Buffering complete -> Playing\n");
    bufferingComplete(player->currentState);

    printf("\n[TEST] Press Pause -> Transition to Paused\n");
    player->clickPauseButton(player);

    printf("\n[TEST] Resume from Paused -> Back to Playing\n");
    player->clickPlayButton(player);

    printf("\n[TEST] Press Stop -> Back to Stopped\n");
    player->clickStopButton(player);

    printf("\n[TEST] Press Play -> Buffering -> Error occurs\n");
    player->clickPlayButton(player);

    bufferingError(player->currentState);

    printf("\n[TEST] In Error state: Try pressing Play\n");
    player->clickPlayButton(player);

    printf("\n[TEST] In Error state: Try pressing Pause\n");
    player->clickPauseButton(player);

    printf("\n[TEST] In Error state: Press Stop to return to Stopped\n");
    player->clickStopButton(player);

    destroyMusicPlayer(player);
    return 0;
}