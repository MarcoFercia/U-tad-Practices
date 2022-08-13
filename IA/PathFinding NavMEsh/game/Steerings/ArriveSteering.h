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

	
	 virtual ResultSteering& GetSteering(const USVec2D& _target) override;
	 virtual void DrawDebug() override;

private:
	USVec2D	 mVelocityDesired;
};