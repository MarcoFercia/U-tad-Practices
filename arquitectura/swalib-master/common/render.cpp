#pragma once
#include"render.h"

#include "logica.h"
#include"Timer.h"

#include <string>
#include "stdafx.h"
#include "font.h"
#include "core.h"
#include "sys.h"



RenderEngine* RenderEn = RenderEngine::Instance();

extern LogicManager* MLogic;

extern m_Timer Timer;


void RenderEngine::initRender()
{
	FONT_Init();	// Characters and symbols inicialization to draw on screen.

	texturas.texbkg = CORE_LoadPNG("data/circle-bkg-128.png", true);
	texturas.texsmallball = CORE_LoadPNG("data/tyrian_ball.png", false);
	texturas.Player = CORE_LoadPNG("data/Player/shoot-1.png", false);
	texturas.background = CORE_LoadPNG("data/Fondo-Nivel-1.png", false);
	texturas.Bullet = CORE_LoadPNG("data/bala/bala-6.png", false);
	texturas.Ball= CORE_LoadPNG("data/red-ball.png", false);

	
	
	// Set up rendering.
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Specifies clear values for the color buffers.
	glMatrixMode(GL_PROJECTION);	// Specifies projection matrix is the current matrix.
	glLoadIdentity();	// Replaces the current matrix with the identity matrix.
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);	// Multiplies the current matrix by an orthographic matrix.
	glEnable(GL_TEXTURE_2D);	// Enabling two-dimensional texturing.
	// NOTA: Mirar diferencias comentando las 2 siguientes funciones.
	glEnable(GL_BLEND);	// Blend the incoming RGBA color values with the values in the color buffers.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blend func. for alpha color.
}



void RenderEngine::RenderGame()
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	

	

	//Llamamos a la funcion creada en la clase LogicManager que se encargara de pintar la logica de este juego,
	//sin que tenga que acceder la clase Render a cosas propias de la logica
	LogicManager::Instance()->pintarlogic(&Timer.fps, &Timer.totaltime, &Timer.timelogic);

	
}

void RenderEngine::shutdownrender()
{
	CORE_UnloadPNG(texturas.texbkg);
	CORE_UnloadPNG(texturas.texsmallball);
	FONT_End();
	
}



textures* RenderEngine::GetTextures()
{
	return &texturas;
}