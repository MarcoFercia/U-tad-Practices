#pragma once

#include "Steering.h"

#include "uslscore/USVec2D.h"

//#include "params.h"
class Character;

class SeekSteering 
{

public:

	explicit SeekSteering(Character* _character);

public:
	  USVec2D GetSteering() ;

	 void SetTarget(const USVec2D& _target);

	  void DrawDebug() ;


	 Character* m_character;
	 USVec2D m_target;

	 USVec2D VelocityDesired;
	 USVec2D Acceleration;


};