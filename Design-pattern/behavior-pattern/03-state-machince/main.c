#include <stdio.h>
#include "inc/bufferingState.h"
#include "inc/errorState.h"
#include "inc/musicPlayer.h"
#include "inc/pausedState.h"
#include "inc/playingState.h"
#include "inc/stoppedState.h"

extern void bufferingComplete(PlayerState* state);
extern void bufferingError(PlayerState* state);

int main() {
    // Initialize the music player in the Stopped state
    MusicPlayer* player = musicPlayerCreate(stoppedStateCreate());

    // --- Stopped State ---
    printf("\n[TEST] Current state: Stopped\n");
    player->clickStopButton(player); // Try stopping again (already stopped)

    // --- Transition to Buffering ---
    printf("\n[TEST] Press Play -> Transition to Buffering\n");
    player->clickPlayButton(player); // Go to Buffering

    // --- Buffering successful -> Playing ---
    printf("\n[TEST] Buffering complete -> Playing\n");
    bufferingComplete(player->currentState); // Simulate successful buffering

    // --- Playing -> Pause ---
    printf("\n[TEST] Press Pause -> Transition to Paused\n");
    player->clickPauseButton(player);

    // --- Paused -> Resume (Play) ---
    printf("\n[TEST] Resume from Paused -> Back to Playing\n");
    player->clickPlayButton(player);

    // --- Playing -> Stop ---
    printf("\n[TEST] Press Stop -> Back to Stopped\n");
    player->clickStopButton(player);

    // --- Stopped -> Buffering -> Error ---
    printf("\n[TEST] Press Play -> Buffering -> Error occurs\n");
    player->clickPlayButton(player); // Buffering

    bufferingError(player->currentState); // Simulate buffering failure

    // --- In Error state -> try all buttons ---
    printf("\n[TEST] In Error state: Try pressing Play\n");
    player->clickPlayButton(player); // Should not respond

    printf("\n[TEST] In Error state: Try pressing Pause\n");
    player->clickPauseButton(player); // Should not respond

    printf("\n[TEST] In Error state: Press Stop to return to Stopped\n");
    player->clickStopButton(player); // Back to Stopped

    // --- End ---
    musicPlayerDestroy(player);
    return 0;
}
