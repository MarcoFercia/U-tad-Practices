#pragma once


#include "Steering.h"
#include "uslscore/USVec2D.h"

//#include "params.h"


class AlignToMovement : public Steering
{
public:

    AlignToMovement(Character* _character);
    ~AlignToMovement();
    virtual void OnUpdate(float _deltatime) override;
    virtual ResultSteering GetSteering() override;
    virtual void DrawDebug() override;

protected:

    float AngularVelocityDesired;

};