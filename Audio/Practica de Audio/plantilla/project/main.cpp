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

using namespace std;


int main()
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(600, 600, "Title", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    ALCdevice* Device = alcOpenDevice(NULL);

    if (Device)
    {
        ALCcontext* Context = alcCreateContext(Device, NULL);
        alcMakeContextCurrent(Context);
    }

    AudioBuffer* pbuffer = AudioBuffer::load("data/music.wav");
    AudioSource* pSource = new AudioSource(pbuffer);
    Listener* pListener = Listener::GetInstance();

    pSource->setPosition(0.f,20.f,0.f);
    alSourcef(pSource->getAlBuffer(), AL_GAIN, 20.f);

    pSource->play();

    while (glfwWindowShouldClose(window) != 1)
    {

        if (glfwGetKey(window, GLFW_KEY_RIGHT))
        {
            ALfloat x, y, z;
            alGetSource3f(pSource->getAlBuffer(), AL_POSITION, &x, &y, &z);

            pSource->setPosition(x + 3.f, y, z);



        }
        if (glfwGetKey(window, GLFW_KEY_LEFT))
        {

            ALfloat x, y, z;
            alGetSource3f(pSource->getAlBuffer(), AL_POSITION, &x, &y, &z);

            pSource->setPosition(x - 3.f, y, z);
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
            pitchvalue = pitchvalue*0.95f;
            pSource->setPitch(pitchvalue);
        }



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
