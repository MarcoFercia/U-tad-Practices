#pragma once

#include "Steering.h"

#include "uslscore/USVec2D.h"

//#include "params.h"
class Character;

class SeekSteering : public Steering
{

public:

	explicit SeekSteering(Character* _character);

public:
	 virtual USVec2D GetSteering() override;

	 void SetTarget(const USVec2D& _target);

	 virtual void DrawDebug() override;


	 Character* m_character;
	 USVec2D m_target;

	 USVec2D VelocityDesired;
	 USVec2D Acceleration;


};