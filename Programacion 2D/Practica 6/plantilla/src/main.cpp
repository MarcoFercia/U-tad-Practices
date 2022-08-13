#pragma once
#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION



#include "litegfx.h"
#include <glfw3.h>
#include <iostream>
#include "main.h"
#include"Vector2.h"
#include"stb_image.h"
#include "Sprite.h"
#include "Collider.h"
#include "World.h"
#include "sreensize.h"
#include <algorithm>



/*using namespace std;*/

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


void MoveBee(Sprite& _spriteref, float _deltatime)
{

    float rotation=0;
    bool fliped = true;

    vec2 BeePosition = _spriteref.getPosition();
    vec2 Direction;

    Direction.x = PosMouse.x - BeePosition.x;
    Direction.y = PosMouse.y - BeePosition.y;

    float angle = _spriteref.getAngle();

    if (Direction.length(Direction) <= 8.f)
    {
    }
    else
    {
        vec2 NormalDirection = Direction.normal(Direction);

        vec2 NewPosition = BeePosition;

        NewPosition.x = BeePosition.x + (NormalDirection.x * (128 * _deltatime));
        NewPosition.y = BeePosition.y + (NormalDirection.y * (128 * _deltatime));

        


        if (PosMouse.x >= NewPosition.x)
        {
            fliped = false;
        }
     
        _spriteref.SetFlipX(fliped);


        if (abs(PosMouse.y - NewPosition.y) < 30)
        {
            rotation = 0;
        }
        else if (PosMouse.y > NewPosition.y)
        {
            rotation = -15;
        }
        else
        {
            rotation = 15;
        }

        if (fliped)
        {
            rotation = -1 * rotation;
        }


        _spriteref.setPosition(NewPosition);
    }


    if (abs(angle - rotation) > 0.5f)
    {
        if (rotation < angle)
        {
            angle = angle - (32 * _deltatime);
        }
        else
        {
            angle = angle + (32 * _deltatime);
        }
    }


    _spriteref.setAngle(angle);
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





    ltex_t* pltexBee = loadTexture("data/bee_anim.png");
    Sprite* pSpriteBee = new Sprite(pltexBee, 8, 1);
    pSpriteBee->setFps(8.f);
    pSpriteBee->setCallback(&MoveBee);
    pSpriteBee->setBlend(BLEND_ALPHA);
    pSpriteBee->setPosition(vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
    pSpriteBee->setAngle(0);
    pSpriteBee->setScale(vec2(1.f, 1.f));
    pSpriteBee->setColor(1, 1, 1, 1);






    ltex_t* pClouds = loadTexture("data/clouds.png");


    ltex_t* pLevel = loadTexture("data/level.png");


    ltex_t* pTrees1 = loadTexture("data/trees1.png");


    ltex_t* pTrees2 = loadTexture("data/trees2.png");




    World* pWorld = new World(0.5f, 0.9f, 06.f, pLevel, pTrees1, pTrees2, pClouds);



    pWorld->setScrollRatio(0, 1.f);
    pWorld->setScrollRatio(1, 0.8f);
    pWorld->setScrollRatio(2, 0.6f);
    pWorld->setScrollRatio(3, 0.4f);
    pWorld->setScrollSpeed(3, vec2(-16.f, -8.f));

    vec2 CameraPos = vec2(0.f, 0.f);

    pWorld->addSprite(*pSpriteBee);







    while (glfwWindowShouldClose(window) != 1)
    {
        DeltaTime += glfwGetTime() - PreviousTime;
        PreviousTime = glfwGetTime();




        //input de usuario
        glfwGetCursorPos(window, &xpos, &ypos);
        PosMouse = vec2(xpos+pWorld->getCameraPosition().x, ypos+pWorld->getCameraPosition().y);

        




        lgfx_clearcolorbuffer(0, 0, 0);


        //pWorld->setCameraPosition(vec2(pWorld->getCameraPosition().x, pWorld->getCameraPosition().y));

        while (DeltaTime >= FIXEDTICK)
        {
            DeltaTime -= FIXEDTICK;

            pWorld->update(FIXEDTICK);

        }
        pWorld->draw(vec2(WINDOW_WIDTH, WINDOW_HEIGHT));


        float Cam = clamp(pSpriteBee->getPosition().x - WINDOW_WIDTH / 2, 0.f, pWorld->getBackground(0)->width- WINDOW_WIDTH );


        pWorld->setCameraPosition(vec2(Cam, 0.f));




        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}
