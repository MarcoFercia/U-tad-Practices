#pragma once
#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define RAD 0.01745329

#include "litegfx.h"
#include <glfw3.h>
#include <iostream>
#include "main.h"
#include"Vector2.h"
#include"stb_image.h"
#include "Sprite.h"

using namespace std;


vec2 PosClick;

const float FIXEDTICK = 1.f / 60.f;

double Time = 0;
double DeltaTime = 0;
double PreviousTime = 0;


double xpos, ypos;
int width, height;

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

void CallSprite(Sprite& _spriteref, float _deltatime)
{
	vec2 BeePosition = _spriteref.getPosition();
	vec2 Direction;

	Direction.x = PosMouse.x - BeePosition.x;
	Direction.y = PosMouse.y - BeePosition.y;

	float angle = _spriteref.getAngle();

	if (Direction.length(Direction) <= 8.f)
	{

		if (angle <=0)
		{
			angle = angle + (32 * _deltatime);
		}

		if (angle >= 0)
		{
			angle = angle + (-32 * _deltatime);
		}

	}
	else
	{
		vec2 NormalDirection = Direction.normal(Direction);

		vec2 NewPosition = BeePosition;

		NewPosition.x = BeePosition.x + (NormalDirection.x * (128 * _deltatime));
		NewPosition.y = BeePosition.y + (NormalDirection.y * (128 * _deltatime));

		if (PosMouse.x >= NewPosition.x)
		{
			_spriteref.SetFlipX(false);

			if (angle > -15)
			{
				angle = angle + (-32 * _deltatime);
			}


		}
		else
		{
			_spriteref.SetFlipX(true);
			if (angle < 15)
			{
				angle = angle + (32 * _deltatime);
			}
		}


		_spriteref.setPosition(NewPosition);
	}

	




	_spriteref.setAngle(angle);
}





int main() 
{
	
	glfwInit();
	GLFWwindow* window= glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"Title",nullptr,nullptr);
	glfwMakeContextCurrent(window);
	lgfx_setup2d(WINDOW_WIDTH, WINDOW_HEIGHT);
	lgfx_clearcolorbuffer(0,0,0);

	
	


	


	
	

	
	ltex_t* pltexBee = loadTexture("data/bee_anim.png");
	Sprite* pBee = new Sprite(pltexBee, 8, 1);
	pBee->setFps(8);
	pBee->setCallback(&CallSprite);
	pBee->setBlend(BLEND_ALPHA);
	pBee->setScale(vec2(60, 60));
	pBee->setPosition(vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	pBee->setAngle(0);
	pBee->setColor(1, 1, 1, 1);
	pBee->setPosition(vec2(200, 400));
	
	PreviousTime = glfwGetTime();


	while (glfwWindowShouldClose(window)!= 1)
	{
		std::string coso = "Angle --> ";
		 coso += stringFromNumber(pBee->getAngle());
		
		 coso += "   Pos.x -->";
		 coso += stringFromNumber(pBee->getPosition().x);
		 coso += "   Pos.y -->";
		 coso += stringFromNumber(pBee->getPosition().y);

		 coso += "   Pos.x -->";
		 coso += stringFromNumber(PosMouse.x);
		 coso += "   Pos.y -->";
		 coso += stringFromNumber(PosMouse.y);


		glfwSetWindowTitle(window, coso.c_str());


		lgfx_clearcolorbuffer(0, 0, 0);


		DeltaTime += glfwGetTime() - PreviousTime;
		PreviousTime = glfwGetTime();


		glfwGetWindowSize(window, &width, &height);
		vec2 SizeWindow(width, height);

		//input de usuario
		glfwGetCursorPos(window, &xpos, &ypos);
		PosMouse = vec2(xpos, ypos);

		//delta time
		while (DeltaTime >= FIXEDTICK)
		{
			DeltaTime -= FIXEDTICK;

			pBee->update(FIXEDTICK);
		}



		lgfx_setblend(BLEND_SOLID);
		lgfx_setcolor(0, 0, 0, 0);
		

		lgfx_drawrect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		
		pBee->draw();




		//cambiamos buffer
	glfwSwapBuffers(window);





		glfwPollEvents();

	}



	
	glfwTerminate();
	return 0;
}
