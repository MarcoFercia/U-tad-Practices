#pragma once


#include "Steering.h"
#include "uslscore/USVec2D.h"
#include "AlignSteering.h"

//#include "params.h"


class AlignToMovement : public Steering
{
public:

    AlignToMovement(Character* _character);
    ~AlignToMovement();

    virtual ResultSteering& GetSteering(float _target) override;
    virtual void DrawDebug() override;

protected:

    float AngularVelocityDesired;
    AlignSteering* mAlignDelegate;
};