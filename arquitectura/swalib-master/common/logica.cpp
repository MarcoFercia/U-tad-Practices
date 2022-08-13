#pragma once
#include"logica.h"

#include"Timer.h"
#include "render.h"
#include "font.h"
#include "vector2d.h"
#include "stdafx.h"
#include "sys.h"
#include "core.h"




LogicManager* MLogic = LogicManager::Instance();

extern m_Timer Timer;

const float MAX_BALL_SPEED = 8.f;

//Creacion de las entidades pelotas y despues la creacion de los diferentes componentes que forman la pelota
void LogicManager::initLogic()
{
	 
	DestroyBalls = NUM_BALLS + (NUM_BALLS * 2);
	for (unsigned int i = 0; i < NUM_BALLS+(NUM_BALLS*2); i++)
	{
		BallList.push_front(new Entity);
	}
	
	int ballactive = 0;
	for (auto Iter = BallList.begin(); Iter != BallList.end(); Iter++)
	{
		(*Iter)->type = Entity::Identifier::Enemy;
		vec2 TPos = vec2(CORE_FRand(0.0, SCR_WIDTH_COLL), CORE_FRand(300.f, SCR_HEIGHT_COLL));
		vec2 TVel = vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), 5 );
		float TRadius = 20.f;
		GLuint TSprite = RenderEngine::Instance()->GetTextures()->Ball;

		(*Iter)->AddComponent(new CollisionComponent(*Iter, TPos,TRadius,TVel));
		(*Iter)->AddComponent(new MovementComponent(*Iter,TPos,TVel));
		(*Iter)->AddComponent(new RenderComponent(*Iter,TPos,TRadius,TSprite));


		if (ballactive <=NUM_BALLS-1)
		{
			(*Iter)->isActive = true;
			(*Iter)->tier = 2;
			ballactive++;
			
		}
		else
		{
			(*Iter)->isActive = false;
			(*Iter)->tier = 1;
		}
	}

	


	Player = new Entity;
	Player->type = Entity::Identifier::Player;
	Player->AddComponent(new CollisionComponent(Player, vec2(320.f, 35.f), 35.f, 0.f));
	Player->AddComponent(new PlayerControllerComponent(Player,vec2(320.f, 35.f),vec2(200,0)));
	Player->AddComponent(new RenderComponent(Player, vec2(320.f,35.f), 35.f, RenderEngine::Instance()->GetTextures()->Player));
	Player->isActive = true;
	
	Bullet = new Entity;
	Bullet->type = Entity::Identifier::Bullet;
	Bullet->AddComponent(new CollisionComponent(Bullet, vec2(0.f,0.f), 20.f, vec2(0.f, 5.f)));
	Bullet->AddComponent(new MovementComponent(Bullet, vec2(0.f, 0.f), vec2(0.f, 300.f)));
	Bullet->AddComponent(new RenderComponent(Bullet, vec2(0.f, 0.f), 20.f, RenderEngine::Instance()->GetTextures()->Bullet));
	Bullet->isActive = false;
	
}

//Llamamos a la funcion Slot de cada entidad bola que a su vez llamara a las funciones slot de los componentes
void LogicManager::LogicSlot()
{
	if (hp <= 0 || DestroyBalls <= 0)
	{
		GameOver = true;
	}

	Timer.initSlots();

	while (Timer.ProcessSlot())
	{

		if (GameOver == false)
		{
			Player->Slot(Timer.fixedtick);
			Bullet->Slot(Timer.fixedtick);
			for (auto Iter = BallList.begin(); Iter != BallList.end(); ++Iter)
			{

				(*Iter)->Slot(Timer.fixedtick * 20);
			}
		}
	}
}


//Devuelve la lista de entidades
std::list<Entity*> *LogicManager::GetBalls()
{
	
	return  &BallList;
}



//Esta funcion se encarga de pintar todo en pantalla
void LogicManager::pintarlogic(float* fps, float* realtime, float* logictime)
{
	
	textures* texturas = RenderEngine::Instance()->GetTextures();

	// Render fondo


	CORE_RenderCenteredSprite(vec2(SCR_WIDTH/2, SCR_HEIGHT/2), vec2(640.f, 480.f), texturas->background);




	
	//Render Pelotas
	for (auto CompIt = BallList.begin(); CompIt != BallList.end(); ++CompIt)
	{
		
		(*CompIt)->FindComponent<RenderComponent>()->CallSlot();

	}

	Player->FindComponent<RenderComponent>()->CallSlot();
	Bullet->FindComponent<RenderComponent>()->CallSlot();

	
	
	

	//Render Text
	std::string realt;
	realt = "HP: ";
	realt = realt + std::to_string(hp);
	FONT_DrawString(vec2(5 , 420), realt.c_str());
	realt = "BALLS REMAINING: ";
	realt = realt + std::to_string(DestroyBalls);
	FONT_DrawString(vec2(120, 420), realt.c_str());
	realt = "FPS: ";
	realt = realt + std::to_string(*fps);
	FONT_DrawString(vec2(460, 420), realt.c_str());


	if (GameOver == true)
	{
		realt = "GAME OVER";
		FONT_DrawString(vec2(SCR_WIDTH / 2 - 6 * 16, SCR_HEIGHT/2), realt.c_str());
	}
	
}

//Llamada para destruir las entidades de la lista pelotas que a su vez cada destructor se encarga de destruir cada componente
void LogicManager::endLogic()
{
	for (auto Iter = BallList.begin(); Iter != BallList.end(); Iter++)
	{
		delete* Iter;
		*Iter = nullptr;
	}
	BallList.clear();
}