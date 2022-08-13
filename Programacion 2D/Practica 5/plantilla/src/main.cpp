#pragma once
#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800


#include "litegfx.h"
#include <glfw3.h>
#include <iostream>
#include "main.h"
#include"Vector2.h"
#include"stb_image.h"
#include "Sprite.h"
#include "Collider.h"
using namespace std;

const float FIXEDTICK = 1.f / 60.f;

double Time = 0;
double DeltaTime = 0;
double PreviousTime = 0;

vec2 PosMouse;

ltex_t* loadTexture(const char* filename)
{
	int ximage = 0, yimage = 0;
	unsigned char* pPtr = stbi_load(filename, &ximage, &yimage, nullptr, 4);
	ltex_t* pLtex = ltex_alloc(ximage, yimage, 1);
	ltex_setpixels(pLtex, pPtr);
	stbi_image_free(pPtr);

	return pLtex;
}


void SetCirclePosRadius(Sprite& _Spriteref, float _deltaTime)
{

    if (_Spriteref.iscollision == true)
    {
		_Spriteref.setColor(1, 0, 0, 1);
    }
    else
    {
		_Spriteref.setColor(1, 1, 1, 1);
    }
	
    _Spriteref.CollisionClass->setPos(_Spriteref.getPosition());
    _Spriteref.CollisionClass->setRadius(_Spriteref.getSize().x/2);

	vec2 Scaleref = _Spriteref.getScale();

    if (_Spriteref.scaleDirection == true)
    {
        Scaleref.x += (0.25f * _deltaTime);
        Scaleref.y += (0.25f * _deltaTime);

        if (Scaleref.x >= 1.1f && Scaleref.y >= 1.1f)
        {
            _Spriteref.scaleDirection = false;
        }
    }

    if (_Spriteref.scaleDirection == false)
    {
        Scaleref.x -= (0.25f * _deltaTime);
        Scaleref.y -= (0.25f * _deltaTime);

        if (Scaleref.x <= 0.9f && Scaleref.y <= 0.9f)
        {
            _Spriteref.scaleDirection = true;
        }
    }

	_Spriteref.setScale(Scaleref);
}


void SetRectPosSize(Sprite& _Spriteref, float _deltaTime)
{

    if (_Spriteref.iscollision == true)
    {
		_Spriteref.setColor(1, 0, 0, 1);
    }
    else
    {
		_Spriteref.setColor(1, 1, 1, 1);
    }

    _Spriteref.CollisionClass->setPos(_Spriteref.getPosition());
    _Spriteref.CollisionClass->setSize(_Spriteref.getSize());


    vec2 Scaleref = _Spriteref.getScale();

    if (_Spriteref.scaleDirection == true)
    {
        Scaleref.x += (0.25f * _deltaTime);
		Scaleref.y += (0.25f * _deltaTime);

        if (Scaleref.x >= 1.1f && Scaleref.y >= 1.1f)
        {
            _Spriteref.scaleDirection = false;
        }
    }

    if (_Spriteref.scaleDirection == false)
    {
        Scaleref.x -= (0.25f * _deltaTime);
		Scaleref.y -= (0.25f * _deltaTime);

        if (Scaleref.x <= 0.9f && Scaleref.y <= 0.9f)
        {
            _Spriteref.scaleDirection = true;
        }
    }


    _Spriteref.setScale(Scaleref);
}


void SetCirclePosRadiusMouse(Sprite& _Spriteref, float _deltaTime)
{

    if (_Spriteref.iscollision == true)
    {
		_Spriteref.setColor(1, 0, 0, 1);
    }
    else
    {
		_Spriteref.setColor(1, 1, 1, 1);
    }

    _Spriteref.CollisionClass->setPos(_Spriteref.getPosition());
    _Spriteref.CollisionClass->setRadius(_Spriteref.getSize().y/2);

}


void SetRectPosSizeMouse(Sprite& _Spriteref, float _deltaTime)
{

    if (_Spriteref.iscollision == true)
    {
		_Spriteref.setColor(1, 0, 0, 1);
    }
    else
    {
		_Spriteref.setColor(1, 1, 1, 1);
    }


    _Spriteref.CollisionClass->setPos(_Spriteref.getPosition());
    _Spriteref.CollisionClass->setSize(_Spriteref.getSize());
}

void SetPixelPosSize(Sprite& _Spriteref, float _deltaTime)
{

    if (_Spriteref.iscollision == true)
    {
		_Spriteref.setColor(1, 0, 0, 1);
    }
    else
    {
		_Spriteref.setColor(1, 1, 1, 1);
    }


    _Spriteref.CollisionClass->setPos(_Spriteref.getPosition());
    _Spriteref.CollisionClass->setSize(_Spriteref.getSize());
}




int main() 
{
	
	glfwInit();
	GLFWwindow* window= glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"Title",nullptr,nullptr);
	glfwMakeContextCurrent(window);
	lgfx_setup2d(WINDOW_WIDTH, WINDOW_HEIGHT);
	lgfx_clearcolorbuffer( 0,0, 0);

	
	
	double xpos, ypos;
	PreviousTime = glfwGetTime();

   



	ltex_t* pltexBee = loadTexture("data/bee.png");
	Sprite* pBeeStatic = new Sprite(pltexBee, 1, 1);
	pBeeStatic->setFps(1);
	pBeeStatic->setBlend(BLEND_ALPHA);
	pBeeStatic->setPosition(vec2((2*WINDOW_WIDTH / 4), WINDOW_HEIGHT / 2));
	pBeeStatic->setAngle(0);
	pBeeStatic->setColor(1, 1, 1, 1);
	pBeeStatic->setCollisionType(Sprite::CollisionType::COLLISION_PIXELS);
	pBeeStatic->setCallback(&SetPixelPosSize);



	ltex_t* pltexBall = loadTexture("data/ball.png");
	Sprite* pBallStatic = new Sprite(pltexBall, 1, 1);
	pBallStatic->setFps(1);
	pBallStatic->setBlend(BLEND_ALPHA);	
	pBallStatic->setPosition(vec2( 1*(WINDOW_WIDTH / 4), WINDOW_HEIGHT / 2));
	pBallStatic->setAngle(0);
	pBallStatic->setColor(1, 1, 1, 1);
	pBallStatic->setCollisionType(Sprite::CollisionType::COLLISION_CIRCLE);
	pBallStatic->setCallback(&SetCirclePosRadius);

	ltex_t* pltexbox = loadTexture("data/box.png");
	Sprite* pBoxStatic = new Sprite(pltexbox, 1, 1);
	pBoxStatic->setFps(1);
	pBoxStatic->setBlend(BLEND_ALPHA);
	pBoxStatic->setPosition(vec2(3 * (WINDOW_WIDTH / 4), WINDOW_HEIGHT / 2));
	pBoxStatic->setAngle(0);
	pBoxStatic->setColor(1, 1, 1, 1);
	pBoxStatic->setCollisionType(Sprite::CollisionType::COLLISION_RECT);
	pBoxStatic->setCallback(&SetRectPosSize);

	ltex_t* pltexcircle = loadTexture("data/circle.png");
	ltex_t* pltexrect = loadTexture("data/rect.png");
	

	Sprite* pMouse = new Sprite(pltexBee, 1, 1);
	pMouse->setColor(1, 1, 1, 1);
	pMouse->setAngle(0);
	pMouse->setBlend(BLEND_ALPHA);
	pMouse->setScale(vec2(1.f, 1.f));
	pMouse->setCallback(&SetPixelPosSize);

	pMouse->setCollisionType(Sprite::CollisionType::COLLISION_PIXELS);



	
    
    



	while (glfwWindowShouldClose(window)!= 1)
	{
		DeltaTime += glfwGetTime() - PreviousTime;
		PreviousTime = glfwGetTime();


        /* std::string coso = "Scale.x --> ";
         coso += stringFromNumber(pBallStatic->getScale().x);

         coso += "   Scale.y -->";
         coso += stringFromNumber(pBallStatic->getScale().y);

         coso += "   Scale.x -->";
         coso += stringFromNumber(pBoxStatic->getScale().x);

         coso += "   Scale.y -->";
         coso += stringFromNumber(pBoxStatic->getScale().y);



         glfwSetWindowTitle(window, coso.c_str());*/



		//input de usuario
		glfwGetCursorPos(window, &xpos, &ypos);
		PosMouse=vec2(xpos, ypos);

		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
		{
			pMouse->setTexture(pltexcircle);
			pMouse->setScale(vec2(2.f, 2.f));
			pMouse->setCollisionType(Sprite::CollisionType::COLLISION_CIRCLE);
			pMouse->setCallback(&SetCirclePosRadiusMouse);
		}
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
        {
			pMouse->setTexture(pltexrect);
			pMouse->setScale(vec2(2.f, 2.f));
			pMouse->setCollisionType(Sprite::CollisionType::COLLISION_RECT);
			pMouse->setCallback(&SetRectPosSizeMouse);
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
        {
			pMouse->setTexture(pltexBee);
			pMouse->setScale(vec2(1.f, 1.f));
			pMouse->setCollisionType(Sprite::CollisionType::COLLISION_PIXELS);
			pMouse->setCallback(&SetPixelPosSize);
        }
        
        
		pMouse->setPosition(PosMouse);
			
		lgfx_clearcolorbuffer(0, 0, 0);

		pMouse->iscollision = false;


		while (DeltaTime >= FIXEDTICK)
		{
			DeltaTime -= FIXEDTICK;

			
			
			


			if (pMouse->collides(*pBallStatic))
			{
				pMouse->iscollision = true;
				pBallStatic->iscollision = true;
			}
			else
			{
				pBallStatic->iscollision = false;
			}

			if (pMouse->collides(*pBeeStatic))
			{
				pMouse->iscollision = true;
				pBeeStatic->iscollision = true;
			}
			else
			{
				pBeeStatic->iscollision = false;
			}

			if (pMouse->collides(*pBoxStatic))
			{
				pMouse->iscollision = true;
				pBoxStatic->iscollision = true;
			}
			else
			{
				pBoxStatic->iscollision = false;
			}

            pBeeStatic->update(FIXEDTICK);
            pBallStatic->update(FIXEDTICK);
            pBoxStatic->update(FIXEDTICK);
            pMouse->update(FIXEDTICK);

		}

	
		pBallStatic->draw();
		pBeeStatic->draw();
		pBoxStatic->draw();
		pMouse->draw();




	


		glfwSwapBuffers(window);

		

		glfwPollEvents();

	}



	delete pBoxStatic;
	delete pBeeStatic;
	delete pBallStatic;
	delete pMouse;


	delete pltexBall;
	delete pltexBee;
	delete pltexbox;
	delete pltexcircle;
	delete pltexrect;
	glfwTerminate();
}
