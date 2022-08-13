#pragma once

#include "stdafx.h"

struct textures
{
	GLuint texbkg;
	GLuint texsmallball;

	GLuint background;
	GLuint Player;
	GLuint Bullet;
	GLuint Ball;

};


//void initRender();
//void renderjuego(float fps, float realtime, float logictime);
//void shutdownrender();


class RenderEngine
{
private:

	textures texturas;


	RenderEngine() {};
	~RenderEngine();
	static RenderEngine* pRenderEngine;

public:

	static RenderEngine* Instance()
	{
		if (pRenderEngine == nullptr)
		{
			pRenderEngine = new RenderEngine;
		}
		return pRenderEngine;
	}

	textures* GetTextures();
	void initRender();
	void RenderGame();
	
	void shutdownrender();

	
};