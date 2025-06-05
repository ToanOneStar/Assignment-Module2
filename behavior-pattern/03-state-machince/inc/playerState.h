#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

// Forward declaration
struct MusicPlayer;
typedef struct PlayerState PlayerState;

// State interface
struct PlayerState {
    void (*pressPlay)(PlayerState *state);
    void (*pressPause)(PlayerState *state);
    void (*pressStop)(PlayerState *state);
    void (*setContext)(PlayerState *state, struct MusicPlayer *player);

    struct MusicPlayer *player; // Context reference
};

#endif
