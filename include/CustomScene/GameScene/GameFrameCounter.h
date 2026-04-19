#ifndef GAME_FRAME_COUNTER_H_
#define GAME_FRAME_COUNTER_H_

// Global frame counter for synchronized enemy behavior in online multiplayer
static int g_gameFrameCount = 0;

inline int GetGameFrameCount() {
    return g_gameFrameCount;
}

inline void IncrementGameFrameCount() {
    g_gameFrameCount++;
}

#endif
