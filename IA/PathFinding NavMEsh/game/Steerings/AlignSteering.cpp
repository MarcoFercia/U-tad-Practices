#include <stdafx.h>
#include "AlignSteering.h"

#include <character.h>
#include <params.h>
#include "AngleOperations.h"


AlignSteering::AlignSteering(Character* _character) : Steering(_character)
{

}

ResultSteering& AlignSteering::GetSteering(float _target)
{
    if (mCharacter)
    {
        const Params& params = mCharacter->GetParams();
        float maxVelocity = params.max_angular_velocity;
        float maxAcceleration =params.max_angular_acceleration;
      
        float arriveRadius = params.angular_arrive_radius;
        float destRadius = params.angular_dest_radius;

        float currentRotation = mCharacter->GetRot();
        float currentAngularVelocity = mCharacter->GetAngularVelocity();



        AnlgesOperations::NormalizeDegAngle(maxVelocity);
        AnlgesOperations::NormalizeDegAngle(maxAcceleration);
        AnlgesOperations::NormalizeDegAngle(_target);
        AnlgesOperations::NormalizeDegAngle(arriveRadius);
        AnlgesOperations::NormalizeDegAngle(destRadius);
        AnlgesOperations::NormalizeDegAngle(currentRotation);
        AnlgesOperations::NormalizeDegAngle(currentAngularVelocity);

        float deltaRotation = _target - currentRotation;
        mAngularVelocityDesired = deltaRotation > 0 ? 1.f : -1.f;
        if (abs(deltaRotation) < destRadius)
        {
            maxVelocity = 0.f;
        }
        else if (abs(deltaRotation) < arriveRadius)
        {
            float factor = abs(deltaRotation) / arriveRadius;
            maxVelocity *= factor;
        }
        mAngularVelocityDesired *= maxVelocity;
        mSteering.angular = mAngularVelocityDesired - currentAngularVelocity > 0.f ? 1.f : -1.f;
        mSteering.angular *= maxAcceleration;
     

    }
    return mSteering;
}

void AlignSteering::DrawDebug()
{

    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

}
