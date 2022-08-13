#pragma once

#include "Steering.h"

#include "uslscore/USVec2D.h"

//#include "params.h"
class Character;

class ArriveSteering : public Steering
{

public:

	explicit ArriveSteering(Character* _character);

public:
	 virtual USVec2D GetSteering() override;


	 virtual void DrawDebug() override;


	 Character* m_character;

	 USVec2D VelocityDesired;
	 USVec2D m_Steering;


};