#pragma once


//#include <character.h>
//#include <params.h>
#include <uslscore/USVec2D.h>



class Steering
{

public:

	 virtual USVec2D GetSteering() = 0;
	 virtual void DrawDebug() = 0;
	
};