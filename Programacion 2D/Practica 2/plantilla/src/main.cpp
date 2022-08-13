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
using namespace std;

ltex_t* loadTexture(const char* filename)
{
	int ximage = 0, yimage = 0;
	unsigned char* pPtr = stbi_load(filename, &ximage, &yimage, nullptr, 4);
	ltex_t* pLtex = ltex_alloc(ximage, yimage, 1);
	ltex_setpixels(pLtex, pPtr);
	stbi_image_free(pPtr);

	return pLtex;
}


int main() 
{
	
	glfwInit();
	GLFWwindow* window= glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"Title",nullptr,nullptr);
	glfwMakeContextCurrent(window);
	lgfx_setup2d(WINDOW_WIDTH, WINDOW_HEIGHT);
	lgfx_clearcolorbuffer( 0,0, 0);

	
	double TBefore=glfwGetTime();
	double TAct;
	double deltaTime;


	double xpos, ypos;
	int width, height;
	


	vec2 PosClick;
	

	
	
	float sizefire = 0.8f;
	bool sizefiredireccion = false;
   float angle=-10;
   bool angledireccion = false;

	
	ltex_t* pltexWall = loadTexture("data/wall.jpg");
	ltex_t* pltexFire= loadTexture("data/fire.png");
	ltex_t* pltexGrille = loadTexture("data/grille.png");
	ltex_t* pltexLight = loadTexture("data/light.png");


	



	while (glfwWindowShouldClose(window)!= 1)
	{


		//delta time
		TAct = glfwGetTime();
		deltaTime = TAct - TBefore;
		TBefore = TAct;


		glfwGetWindowSize(window, &width, &height);
		vec2 SizeWindow(width, height);

		

		//input de usuario
		glfwGetCursorPos(window, &xpos, &ypos);
		vec2 PosMouse(xpos, ypos);
		
		
		

		//Actualizamos logica
		

		//Giro del angulo de la llama
		if (angle <= -10)
		{
			angle = angle + (10 * deltaTime);
			angledireccion = false;
		}
		else if (angle >= 10)
		{
			angle = angle + (-10 * deltaTime);
			angledireccion = true;
		}
		else if (angledireccion == false)
		{
			angle = angle + (10 * deltaTime);
		}
		else if(angledireccion==true)
		{
			angle = angle + (-10 * deltaTime);
		}


		//Escalado de la llama
		if (sizefire <= 0.8f)
		{
			sizefire = sizefire + (0.5f * deltaTime);
			angledireccion = false;
		}
		else if (sizefire >= 1.2f)
		{
			sizefire = sizefire + (-0.5f * deltaTime);
			angledireccion = true;
		}
		else if (angledireccion == false)
		{
			sizefire = sizefire + (0.5f * deltaTime);
		}
		else if (angledireccion == true)
		{
			sizefire = sizefire + (-0.5f * deltaTime);
		}
		
		//limpiamos el backbuffer
		

		lgfx_clearcolorbuffer(0, 0, 0);


		//Renderizar escenas
		
		lgfx_setblend(BLEND_SOLID);
		ltex_drawrotsized(pltexWall, 0, 0, 0, 0, 0, 600, 600, 0, 0, 1.45, 1.98);
		lgfx_setblend(BLEND_ADD);
		ltex_drawrotsized(pltexFire, PosMouse.x, PosMouse.y, angle, 0.5f, 0.8f, 200*sizefire, 200*sizefire, 0, 0, 1, 1);
		lgfx_setblend(BLEND_ALPHA);
		ltex_drawrotsized(pltexGrille, 0, 0, 0, 0, 0, 600, 600, 0, 0, 2.93, 2.93);
		lgfx_setblend(BLEND_SOLID);
		lgfx_setcolor(0, 0, 0, 1);

		
		lgfx_drawrect(PosMouse.x  -2300, PosMouse.y - 2300, 2000, 2000);
		lgfx_drawrect(PosMouse.x - 2300, PosMouse.y + 300, 2000, 2000);
		lgfx_drawrect(PosMouse.x - 2300, PosMouse.y - 300, 2000, 600);

		lgfx_drawrect(PosMouse.x + 300, PosMouse.y  -2300, 2000, 2000);
		lgfx_drawrect(PosMouse.x + 300, PosMouse.y + 300, 2000, 2000);
		lgfx_drawrect(PosMouse.x + 300, PosMouse.y - 300, 2000, 600);
		
		lgfx_drawrect(PosMouse.x - 300, PosMouse.y - 2300, 600, 2000);
		
		lgfx_drawrect(PosMouse.x - 300, PosMouse.y + 300, 600, 2000);

		lgfx_setblend(BLEND_MUL);
		lgfx_setcolor(1, 1, 1, 1);
		ltex_drawrotsized(pltexLight, PosMouse.x, PosMouse.y, 0, 0.5f, 0.5f, 600, 600, 0, 0, 1, 1);





		//cambiamos buffer
	glfwSwapBuffers(window);

		
		
		




	//Procesamos eventos
	


		glfwPollEvents();

	}



	ltex_free(pltexWall);
	ltex_free(pltexFire);
	ltex_free(pltexGrille);
	ltex_free(pltexLight);
	glfwTerminate();
}
