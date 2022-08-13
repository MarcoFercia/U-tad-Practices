#include <stdafx.h>
#include "AlignSteering.h"

#include <character.h>
#include <params.h>


AlignSteering::AlignSteering(Character* _character) : m_character(_character), VelocityDesired(0.f), steering(0.f)
{

}

float AlignSteering::GetSteering()
{
    if (m_character)
    {
        const Params& params = m_character->GetParams();
        float maxVelocity = ToRadians(params.max_angular_velocity);
        float maxAcceleration = ToRadians(params.max_angular_acceleration);
        float target = ToRadians(params.target_rotation);
        float arriveRadius = ToRadians(params.angular_arrive_radius);
        float destRadius = ToRadians(params.angular_dest_radius);
        float currentRotation = ToRadians(m_character->GetRot());
        float currentAngularVelocity = ToRadians(m_character->GetAngularVelocity());



        NormalizeAngle(maxVelocity);
        NormalizeAngle(maxAcceleration);
        NormalizeAngle(target);
        NormalizeAngle(arriveRadius);
        NormalizeAngle(destRadius);
        NormalizeAngle(currentRotation);
        NormalizeAngle(currentAngularVelocity);

        float deltaRotation = target - currentRotation;
        VelocityDesired = deltaRotation > 0 ? 1.f : -1.f;
        if (abs(deltaRotation) < destRadius)
        {
            maxVelocity = 0.f;
        }
        else if (abs(deltaRotation) < arriveRadius)
        {
            float factor = abs(deltaRotation) / arriveRadius;
            maxVelocity *= factor;
        }
        VelocityDesired *= maxVelocity;
        steering = VelocityDesired - currentAngularVelocity > 0.f ? 1.f : -1.f;
        steering *= maxAcceleration;
        return ToDegrees(steering);

    }
    return 0.f;
}




void AlignSteering::DrawDebug()
{

    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();


    gfxDevice.SetPenColor(USColorVec(1.f, 0.f, 0.f, 1.f));
    USVec2D position = m_character->GetLoc();
    float target = ToRadians(m_character->GetParams().target_rotation);
    NormalizeAngle(target);

    USVec2D delta = position + USVec2D(cosf(VelocityDesired), sinf(VelocityDesired)) * 50.f;

    MOAIDraw::DrawLine(position.mX, position.mY, delta.mX, delta.mY);


}

void AlignSteering::NormalizeAngle(float& angleInRadians)
{
    if (angleInRadians < -float(PI) || angleInRadians > float(PI))
    {
        int x = int(fmodf(angleInRadians, PI));
        angleInRadians += 2 * float(PI) * -1.f * float(x);
    }
}

float AlignSteering::ToRadians(float angleInDegrees)
{
    float x = angleInDegrees * float(PI) / 180.f;
    return x;
}

float AlignSteering::ToDegrees(float angleInRadians)
{
    float x = angleInRadians * 180.f / float(PI);
    return x;
}
