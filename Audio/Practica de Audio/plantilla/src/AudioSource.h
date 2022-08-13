#pragma once
#include "AudioBuffer.h"
#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"


class AudioSource
{
public:


    AudioSource(AudioBuffer* buffer);

    void setPitch(float pitch);
    void setGain(float gain);
    void setLooping(bool loop);
    void setPosition(float x, float y, float z);
    void setVelocity(float x, float y, float z);
   
    uint32_t getAlBuffer() const;

    void play();
    void stop();
    void pause();
    bool isPlaying() const;



private:

    AudioBuffer* soundbuffer = nullptr;
    bool state;
    ALuint* SourceID;

};