#pragma once

#include "Steering.h"

#include "uslscore/USVec2D.h"
#include "ArriveSteering.h"

//#include "params.h"
class Character;

class PathFollowing : public Steering
{

public:

	PathFollowing(Character* _character);
	 ~PathFollowing();

public:


	 virtual ResultSteering& GetSteering(const USVec2D& _target) override;
	 virtual void DrawDebug() override;

private:

	USVec2D mTarget;
	USVec2D mClosest;
	USVec2D mProjection;
	ArriveSteering* mArriveSteering;
};