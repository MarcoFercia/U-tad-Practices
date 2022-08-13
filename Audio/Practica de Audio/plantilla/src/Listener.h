#pragma once


class Listener
{

private:
    Listener();

   



public:

    static Listener* GetInstance()
    {
        if (!ListenerRef)
        {
            ListenerRef = new Listener;
        }
        return ListenerRef;
    }

    void setListenerPosition(float x, float y, float z);
    void setListenerVelocity(float x, float y, float z);
    void setListenerOrientation(float x, float y, float z);

    static Listener* ListenerRef;
};