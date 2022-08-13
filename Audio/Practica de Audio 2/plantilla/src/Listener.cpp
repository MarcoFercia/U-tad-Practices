#include "Listener.h"
#include "AL/al.h"


Listener* Listener::ListenerRef = nullptr;

Listener::Listener()
{
   


    setListenerPosition(0.f, 0.f, 0.f);
    setListenerVelocity(0.f, 0.f, 0.f);
    setListenerOrientation(0.f, 0.f, 0.f);

}

void Listener::setListenerPosition(float x, float y, float z)
{
    alListener3f(AL_POSITION, x, y, z);
}

void Listener::setListenerVelocity(float x, float y, float z)
{
    alListener3f(AL_VELOCITY, x, y, z);
}

void Listener::setListenerOrientation(float x, float y, float z)
{
    alListener3f(AL_ORIENTATION, x, y, z);
}

