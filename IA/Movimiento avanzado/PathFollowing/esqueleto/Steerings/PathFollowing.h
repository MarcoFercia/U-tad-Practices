#pragma once

#include "Steering.h"

#include "uslscore/USVec2D.h"

//#include "params.h"
class Character;

class PathFollowing : public Steering
{

public:

	PathFollowing(Character* _character);
	 ~PathFollowing();

public:

	 virtual void OnUpdate(float _deltatime) override;
	 virtual ResultSteering GetSteering() override;
	 virtual void DrawDebug() override;

private:

	USVec2D mTarget;
	USVec2D mClosest;
	USVec2D mProjection;
};