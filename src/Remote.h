//
// Created by smarc on 09/11/2025.
//

#ifndef MINIKEYBOARD_REMOTE_H
#define MINIKEYBOARD_REMOTE_H

#include "HID.h"
//================================================================================
//================================================================================
//	Remote

#define REMOTE_CLEAR 0
#define VOLUME_UP 1
#define VOLUME_DOWN 2
#define VOLUME_MUTE 4
#define REMOTE_PLAY_PAUSE 8
#define REMOTE_PAUSE 16
#define REMOTE_STOP 32
#define REMOTE_NEXT 64
#define REMOTE_PREVIOUS 128
#define REMOTE_FAST_FORWARD 256
#define REMOTE_REWIND 512

class Remote_
{
private:
public:
    Remote_();
    void begin();
    void end();

    // Volume
    void increase();
    void decrease();
    void mute();

    // Playback
    void play_pause();
    void pause();
    void stop();

    // Track Controls
    void next();
    void previous();
    void forward();
    void rewind();

    // Send an empty report to prevent repeated actions
    void clear();
};
extern Remote_ Remote;

#endif //MINIKEYBOARD_REMOTE_H