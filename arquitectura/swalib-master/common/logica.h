#pragma once


#include "Components.h"
#include <list>

const unsigned int NUM_BALLS = 5;

class LogicManager
{
private:
	LogicManager() {};
	
	static LogicManager* pManager;

public:
	
	 std::list<Entity*> BallList;
	 Entity* Player = nullptr;
	 Entity* Bullet = nullptr;
	

	 void initLogic();
	 void LogicSlot();
	 void endLogic();
	 void pintarlogic(float* fps, float* realtime, float* logictime);
	 std::list<Entity*>* GetBalls();
	 ~LogicManager();

	 bool GameOver = false;
	 int DestroyBalls = 0;
	 int hp = 3;




	 static  LogicManager* Instance()
	 {
		 if (pManager == nullptr)
		 {
			 pManager = new LogicManager;
		 }
		 return pManager;
	 }

	 

	
};