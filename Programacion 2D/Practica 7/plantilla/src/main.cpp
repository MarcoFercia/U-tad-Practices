#pragma once
#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION



#include "litegfx.h"
#include <glfw3.h>
#include "World.h"
#include "sreensize.h"
#include <algorithm>
#include "stb_image.h"


struct Data
{
    Data(GLFWwindow* _window, World* _world, ltex_t* _idle, ltex_t* _run)
    {
        window = _window;
        world = _world;
        idle = _idle;
        run = _run;
    }

    GLFWwindow* window;
    World* world;
    ltex_t* idle;
    ltex_t* run;

    vec2 velocity;
    bool jump;



};




const float FIXEDTICK = 1.f / 60.f;

double Time = 0;
double DeltaTime = 0;
double PreviousTime = 0;

vec2 PosMouse;

float clamp(float _value, float _min, float _max)
{
    if (_value < _min)
    {
        return _min;
    }
    else if (_value > _max)
    {
        return _max;
    }
    else
    {
        return _value;
    }
}


ltex_t* loadTexture(const char* filename)
{
    int ximage = 0, yimage = 0;
    unsigned char* pPtr = stbi_load(filename, &ximage, &yimage, nullptr, 4);
    ltex_t* pLtex = ltex_alloc(ximage, yimage, 1);
    ltex_setpixels(pLtex, pPtr);
    stbi_image_free(pPtr);

    return pLtex;
}


void MovePlayer(Sprite& _spriteref, float _deltatime)
{
    Data* data = reinterpret_cast<Data*>(_spriteref.getUserData());

    vec2 velocity = vec2(0, 9.8f * _deltatime + data->velocity.y);
   
  

    if (glfwGetKey(data->window, GLFW_KEY_RIGHT))
    {
        if (data->jump)
        {
            velocity.x = velocity.x +( 60 * _deltatime);
        }
        else
        {
            velocity.x = velocity.x + (80 * _deltatime);
        }

        _spriteref.SetFlipX(false);
    }

    if (glfwGetKey(data->window, GLFW_KEY_LEFT))
    {
        if (data->jump)
        {
            velocity.x = velocity.x - (60 * _deltatime);
        }
        else
        {
            velocity.x = velocity.x - (80 * _deltatime);
        }

        _spriteref.SetFlipX(true);
    }


    if (glfwGetKey(data->window, GLFW_KEY_UP) && !data->jump)
    {
        velocity = velocity + vec2(0, -6);
        data->jump = true;
    }

    if (data->world->moveSprite(_spriteref, velocity))
    {
        velocity.y = 0;
        data->jump = false;
    }

    if(velocity.x!=0.f)
    {
        _spriteref.setTexture(data->run, 6, 1);
        _spriteref.setFps(12);
    }
    else
    {
        _spriteref.setTexture(data->idle, 1, 1);
        _spriteref.setFps(1);
    }
    data->velocity = velocity;
    _spriteref.setUserData(data);

}








int main()
{

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Title", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    lgfx_setup2d(WINDOW_WIDTH, WINDOW_HEIGHT);
    lgfx_clearcolorbuffer(0, 0, 0);



    double xpos, ypos;
    PreviousTime = glfwGetTime();


    ltex_t* pClouds = loadTexture("data/clouds.png");



    World* pWorld = new World(0.5f, 0.9f, 06.f, pClouds);
    pWorld->setScrollRatio(0, 0.4f);
    pWorld->setScrollSpeed(0, vec2(-16.f, -8.f));
    pWorld->setScreenSize(vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    pWorld->loadMap("data/map.tmx", 0);



    ltex_t* pltexidle = loadTexture("data/idle.png");
    ltex_t* pltexrun = loadTexture("data/run.png");
    Sprite* pPlayer = new Sprite(pltexidle, 1, 1);
   // pPlayer->setScale(vec2(WINDOW_WIDTH / 1024, WINDOW_HEIGHT / 1024));
    pPlayer->setScale(vec2(1, 1));
    pPlayer->setPosition(vec2(120.f, 305.f));
    pPlayer->setCollisionType(Sprite::CollisionType::COLLISION_RECT);
    pPlayer->setCallback(&MovePlayer);
   
  
    Data data(window, pWorld, pltexidle, pltexrun);
    pPlayer->setUserData(&data);

    vec2 CameraPos = vec2(0.f, 0.f);
    //pWorld->addSprite(*pPlayer);







    while (glfwWindowShouldClose(window) != 1)
    {
        DeltaTime += glfwGetTime() - PreviousTime;
        PreviousTime = glfwGetTime();




        //input de usuario
        glfwGetCursorPos(window, &xpos, &ypos);
        PosMouse = vec2(xpos+pWorld->getCameraPosition().x, ypos+pWorld->getCameraPosition().y);

        




        lgfx_clearcolorbuffer(0, 0, 0);



        while (DeltaTime >= FIXEDTICK)
        {
            DeltaTime -= FIXEDTICK;

            pWorld->update(FIXEDTICK);
            pPlayer->update(FIXEDTICK);
           
        }
        pWorld->draw(vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
        pPlayer->draw();

       


      //  pWorld->setCameraPosition(vec2(Cam, 0.f));




        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}
