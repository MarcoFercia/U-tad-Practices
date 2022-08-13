#pragma once
#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"
#include <stdint.h>


class AudioBuffer
{

private:

    AudioBuffer(ALuint _iBufferID);

public:

    ~AudioBuffer();


    static AudioBuffer* load(const char* filename);

    //uint32_t getAlBuffer() const;
    uint32_t getAlBuffer() const;

    

    ALenum bufferformat = 0;
    ALsizei size = 0;
    ALsizei frequency = 0;
    ALvoid* data;
    ALuint bufferID;

};