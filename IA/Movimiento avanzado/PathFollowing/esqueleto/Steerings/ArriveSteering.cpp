#include <stdafx.h>
#include "ArriveSteering.h"

#include <character.h>
#include <params.h>


ArriveSteering::ArriveSteering(Character* _character) : Steering(_character)
{

}

ArriveSteering::~ArriveSteering()
{
}

void ArriveSteering::OnUpdate(float _deltatime)
{
    if (mCharacter)
    {


        const Params& params = mCharacter->GetParams();

        mSteering.linear = USVec2D();
        mSteering.angular = 0.f;

        mVelocityDesired = params.targetPosition - mCharacter->GetLoc();
        const float distanceToTarget = mVelocityDesired.Length();
        float maxVelocity = distanceToTarget <= params.dest_radius ? 0.f : params.max_velocity;

        const float arriveRadius = params.arrive_radius;
        if (distanceToTarget < arriveRadius)
        {
            const float factor = distanceToTarget / arriveRadius;
            maxVelocity *= factor;
        }

        mVelocityDesired.NormSafe();
        mVelocityDesired *= maxVelocity;

        USVec2D accel = mVelocityDesired - mCharacter->GetLinearVelocity();
        accel.NormSafe();

        mSteering.linear = (accel * params.max_acceleration);




    }
}

ResultSteering ArriveSteering::GetSteering() 
{
  
    return mSteering;
}


void ArriveSteering::DrawDebug() 
{

    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();


//     //DesiredVelocity
//     USVec2D pos = mCharacter->GetLoc();
//     USVec2D delta = pos + mVelocityDesired;
// 
//     gfxDevice.SetPenColor(1.0f, 0.0f, 0.f, 1.0f);
//     MOAIDraw::DrawLine(pos.mX, pos.mY, delta.mX, delta.mY);
// 
// 
//     //Acceleration
//     delta = pos + mSteering.linear;
//     gfxDevice.SetPenColor(1.f, 1.0f, 1.f, 1.0f);
//     MOAIDraw::DrawLine(pos.mX, pos.mY, delta.mX, delta.mY);
}
