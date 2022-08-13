#pragma once



#include "uslscore/USVec2D.h"
#include "Steering.h"

//#include "params.h"
class Character;

class AlignSteering : public Steering
{

public:

	 AlignSteering(Character* _character);

public:
	 
	virtual ResultSteering& GetSteering(float _target) override;
    virtual void DrawDebug() override;
protected:
	 float mAngularVelocityDesired;
};