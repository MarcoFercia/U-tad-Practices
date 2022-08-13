#include "AudioSource.h"





AudioSource::AudioSource(AudioBuffer* buffer)
{
    ALuint* temp = new ALuint;
    alGenSources(1, temp);
    soundbuffer = buffer;

    alSourcei(*temp, AL_BUFFER, buffer->getAlBuffer());

    SourceID = temp;

}




void AudioSource::setPitch(float pitch)
{
    alSourcef(*SourceID, AL_PITCH, pitch);
}

void AudioSource::setGain(float gain)
{
    alSourcef(*SourceID, AL_GAIN, gain);
}

void AudioSource::setLooping(bool loop)
{
    alSourcei(*SourceID, AL_LOOPING, 1);
}

void AudioSource::setPosition(float x, float y, float z)
{
    alSource3f(*SourceID, AL_POSITION, x, y, z);
}

void AudioSource::setVelocity(float x, float y, float z)
{
    alSource3f(*SourceID, AL_VELOCITY, x, y, z);
}

uint32_t AudioSource::getAlBuffer() const
{
    return *SourceID;
}

void AudioSource::play()
{
    alSourcePlay(*SourceID);
    state = true;
}

void AudioSource::stop()
{
    alSourceStop(*SourceID);
    state = false;
}

void AudioSource::pause()
{
    alSourcePause(*SourceID);
    state = false;
}

bool AudioSource::isPlaying() const
{
    return state;
}
