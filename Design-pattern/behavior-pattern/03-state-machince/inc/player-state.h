#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

struct MusicPlayer;
typedef struct PlayerState PlayerState;

struct PlayerState {
    void (*pressPlay)(PlayerState* state);
    void (*pressPause)(PlayerState* state);
    void (*pressStop)(PlayerState* state);
    void (*setContext)(PlayerState* state, struct MusicPlayer* player);

    struct MusicPlayer* player;
};

#endif // PLAYER_STATE_H