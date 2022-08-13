#include <stdafx.h>
#include "AlignToMovement.h"
#include "AngleOperations.h"
#include <character.h>
#include <params.h>

AlignToMovement::AlignToMovement(Character* _character) : Steering(_character)
{

}

AlignToMovement::~AlignToMovement()
{

}

void AlignToMovement::OnUpdate(float _deltatime)
{
    if (mCharacter)
    {
        USVec2D nextLinearVel = mCharacter->GetLinearVelocity();
        float target = AnlgesOperations::ToDegrees(atan2f(nextLinearVel.mY, nextLinearVel.mX));

        const Params& params = mCharacter->GetParams();
        float maxVelocity = params.max_angular_velocity;
        float maxAcceleration = params.max_angular_acceleration;
        float arriveRadius = params.angular_arrive_radius;
        float destRadius = params.angular_dest_radius;
        float currentRotation = mCharacter->GetRot();
        float currentAngularVelocity = mCharacter->GetAngularVelocity();

        AnlgesOperations::NormalizeDegAngle(maxVelocity);
        AnlgesOperations::NormalizeDegAngle(maxAcceleration);
        AnlgesOperations::NormalizeDegAngle(target);
        AnlgesOperations::NormalizeDegAngle(arriveRadius);
        AnlgesOperations::NormalizeDegAngle(destRadius);
        AnlgesOperations::NormalizeDegAngle(currentRotation);
        AnlgesOperations::NormalizeDegAngle(currentAngularVelocity);

        float deltaRot = target - currentRotation;
        AngularVelocityDesired = deltaRot > 0 ? 1.f : -1.f;
        if (abs(deltaRot) < destRadius)
        {
            maxVelocity = 0.f;
        }
        else if (abs(deltaRot) < arriveRadius)
        {
            float factor = abs(deltaRot) / arriveRadius;
            maxVelocity *= factor;
        }
        AngularVelocityDesired *= maxVelocity;

        mSteering.angular = AngularVelocityDesired - currentAngularVelocity > 0.f ? 1.f : -1.f;
        mSteering.angular *= maxAcceleration;
    }
}

ResultSteering AlignToMovement::GetSteering()
{
        return mSteering;  
}

void AlignToMovement::DrawDebug()
{

}
