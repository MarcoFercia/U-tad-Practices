#pragma once
#define LITE_GFX_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600


#include "litegfx.h"
#include <glfw3.h>
#include <time.h>
#include "main.h"
#include"Font.h"



const int MAXDRAWS = 10;
const float FIXEDTICK = 1.f / 60.f;
const float FMAXSPEED = 200.f;
const float FMINSPEED = 20.f;

const char* TEXT = "Hello World";



struct ToDraw 
{
	Font* font = nullptr;
	vec2 position;
	float speed;
	float color[3];
};

float GetRand() {
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

vec2 GetPos() {
	return vec2(
		WINDOW_WIDTH,
		GetRand() * static_cast<float>(WINDOW_HEIGHT)
	);
}


void Update(ToDraw* _draw)
{
	for (ToDraw* it = _draw; it < _draw + MAXDRAWS; it++)
	{
		if (it->position.x + it->font->getTextSize(TEXT).x > 0) 
		{
			it->position.x -= (it->speed * FIXEDTICK);
		}
		else
		{
			it->position.x = WINDOW_WIDTH;
		}	
	}
}


void Draw(ToDraw* _draw)
{
	for (ToDraw* it = _draw; it < _draw + MAXDRAWS; it++)
	{
		lgfx_setcolor(it->color[0], it->color[1], it->color[2], 1);
		it->font->draw(TEXT, it->position);
	}
}


using namespace std;

int main() 
{
	glfwInit();
	srand(time(0));

	double Time = 0;
	double DeltaTime = 0;
	double PreviousTime = 0;
	

	GLFWwindow* window= glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"Title",nullptr,nullptr);

	glfwMakeContextCurrent(window);

	lgfx_setup2d(WINDOW_WIDTH, WINDOW_HEIGHT);

	lgfx_clearcolorbuffer( 0,0, 0);

	Font* pttf1 = Font::load("data/Orange.ttf", 30);
	Font* pttf2 = Font::load("data/SFSlapstickComic.ttf", 30);
	
	if (!(pttf1 && pttf2))
	{
		return -1;
	}
	
	ToDraw draws[MAXDRAWS];

	for (ToDraw* iter = draws; iter < draws + MAXDRAWS; iter++)
	{
		if (GetRand() == 0)
		{
			iter->font = pttf1;
		}
		else
		{
			iter->font = pttf2;
		}
		iter->position = GetPos();
		iter->speed = (GetRand() * (FMAXSPEED - FMINSPEED)) + FMINSPEED;
		for (float* ColorIter = iter->color; ColorIter < iter->color + 3; ColorIter++)
		{
			*ColorIter = GetRand();
		}
	}
	

	bool shouldDraw = false;

	PreviousTime = glfwGetTime();

	
	

	while (glfwWindowShouldClose(window)!= 1)
	{
		DeltaTime += glfwGetTime() - PreviousTime;
		PreviousTime = glfwGetTime();

		lgfx_clearcolorbuffer(0, 0, 0);
		lgfx_setblend(BLEND_ALPHA);
		

		while (DeltaTime >= FIXEDTICK)
		{
			DeltaTime -= FIXEDTICK;
			shouldDraw = true;
			Update(draws);
		}

	
		if (shouldDraw)
		{
			Draw(draws);
		}

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
