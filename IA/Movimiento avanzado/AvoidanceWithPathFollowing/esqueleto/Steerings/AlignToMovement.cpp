#include <stdafx.h>
#include "AlignToMovement.h"
#include "AngleOperations.h"
#include <character.h>
#include <params.h>
#include "AngleOperations.h"

AlignToMovement::AlignToMovement(Character* _character) : Steering(_character)
{
    mAlignDelegate = new AlignSteering(_character);
}

AlignToMovement::~AlignToMovement()
{
    delete mAlignDelegate;
}



ResultSteering& AlignToMovement::GetSteering(float _target)
{

    if(mCharacter)
    {
        USVec2D nextLinearVelocity = mCharacter->GetLinearVelocity();
        float target = AnlgesOperations::ToDegrees(atan2f(nextLinearVelocity.mY, nextLinearVelocity.mX));

        mSteering = mAlignDelegate->GetSteering(target);
      
    }

    return mSteering;
   
}

void AlignToMovement::DrawDebug()
{

}
