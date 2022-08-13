#pragma once

#include "Steering.h"

#include "uslscore/USVec2D.h"

//#include "params.h"
class Character;

class ArriveSteering : public Steering
{

public:

	 ArriveSteering(Character* _character);
	 ~ArriveSteering();

public:

	 virtual void OnUpdate(float _deltatime) override;
	 virtual ResultSteering GetSteering() override;
	 virtual void DrawDebug() override;

private:
	USVec2D	 mVelocityDesired;
};