#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"


#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#include <glfw3.h>
#include <sstream>
#include <vector>

#include <fstream>     
#include <iterator>
#include "../src/AudioBuffer.h"
#include "../src/AudioSource.h"
#include "../src/Listener.h"
#include "litegfx.h"
#include "../src/Vector2.h"

#define RAD 0.01745329

using namespace std;

const float FIXEDTICK = 1.f / 60.f;

double Time = 0;
double DeltaTime = 0;
double PreviousTime = 0;


int main()
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(600, 600, "Title", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    lgfx_setup2d(600, 600);
    lgfx_clearcolorbuffer(0, 0, 0);
    ALCdevice* Device = alcOpenDevice(NULL);

    if (Device)
    {
        ALCcontext* Context = alcCreateContext(Device, NULL);
        alcMakeContextCurrent(Context);
    }


    float deg = 0;
    PreviousTime = glfwGetTime();


    AudioBuffer* pbuffer = AudioBuffer::load("data/music.wav");
   // AudioBuffer* pbuffer = AudioBuffer::load("data/file1.wav");
    AudioSource* pSource = new AudioSource(pbuffer);
    Listener* pListener = Listener::GetInstance();



    vec2 ListenerPos, AudioSourcePos;
    AudioSourcePos = vec2(0.f, 20.f);
    ListenerPos = vec2(300.f, 550.f);

    vec2 ListenerVel, AudioSourceVel;



    pSource->setPosition(AudioSourcePos.x, AudioSourcePos.y, 0.f);

    alSourcef(pSource->getAlBuffer(), AL_GAIN, 20.f);
    alSourcei(pSource->getAlBuffer(), AL_LOOPING, 1);

    pSource->play();


    alDopplerFactor(10);

    while (glfwWindowShouldClose(window) != 1)
    {
        DeltaTime += glfwGetTime() - PreviousTime;
        PreviousTime = glfwGetTime();

        ListenerVel = vec2(0.f, 0.f);

        if (glfwGetKey(window, GLFW_KEY_RIGHT))
        {

            ListenerPos = vec2(ListenerPos.x + (60.f * FIXEDTICK), ListenerPos.y);
            pListener->setListenerPosition(ListenerPos.x, ListenerPos.y, 0.f);
            ListenerVel = vec2(60 * FIXEDTICK);



        }
        if (glfwGetKey(window, GLFW_KEY_LEFT))
        {

            ListenerPos = vec2(ListenerPos.x - (60.f * FIXEDTICK), ListenerPos.y);
            pListener->setListenerPosition(ListenerPos.x, ListenerPos.y, 0.f);
            ListenerVel = vec2(60 * FIXEDTICK * -1);

        }
        if (glfwGetKey(window, GLFW_KEY_UP))
        {

            ALfloat pitchvalue;
            alGetSourcef(pSource->getAlBuffer(), AL_PITCH, &pitchvalue);
            pitchvalue = pitchvalue * 1.05f;
            pSource->setPitch(pitchvalue);


        }
        if (glfwGetKey(window, GLFW_KEY_DOWN))
        {

            ALfloat pitchvalue;
            alGetSourcef(pSource->getAlBuffer(), AL_PITCH, &pitchvalue);
            pitchvalue = pitchvalue * 0.95f;
            pSource->setPitch(pitchvalue);
        }


        while (DeltaTime >= FIXEDTICK)
        {
            DeltaTime -= FIXEDTICK;


            AudioSourcePos.x = (600 / 2) + (600 / 4) * cos(deg * RAD);
            AudioSourcePos.y = (600 / 2) + (600 / 4) * sin(deg * RAD);
            deg += (-32 * FIXEDTICK);

            AudioSourceVel = vec2((600 / 4) * FIXEDTICK * cos(deg * RAD), (600 / 4) * FIXEDTICK * sin(deg * RAD));

            if (deg > 360.f)
            {
                deg -= 360;
            }


        }
        pListener->setListenerVelocity(ListenerVel.x, ListenerVel.y, 0.f);
        pListener->setListenerPosition(ListenerPos.x, ListenerPos.y, 0.f);

        pSource->setPosition(AudioSourcePos.x, AudioSourcePos.y, 0.f);
        pSource->setVelocity(AudioSourceVel.x, AudioSourceVel.y, 0.f);


        lgfx_clearcolorbuffer(0, 0, 0);




        lgfx_setcolor(1, 1, 1, 0);
        lgfx_drawoval(ListenerPos.x, ListenerPos.y, 20.f, 20.f);

        lgfx_setcolor(1, 0, 0, 0);
        lgfx_drawoval(AudioSourcePos.x, AudioSourcePos.y, 20.f, 20.f);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
