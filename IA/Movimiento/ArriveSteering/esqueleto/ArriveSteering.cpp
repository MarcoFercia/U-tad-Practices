#include <stdafx.h>
#include "ArriveSteering.h"

#include <character.h>
#include <params.h>


ArriveSteering::ArriveSteering(Character* _character) : m_character(_character)
{

}

USVec2D ArriveSteering::GetSteering() 
{
    if (m_character)
    {
        const Params& params = m_character->GetParams();

        VelocityDesired = params.targetPosition - m_character->GetLoc();
        const float distanceToTarget = VelocityDesired.Length();
        float maxVelocity = distanceToTarget <= params.dest_radius ? 0.f : params.max_velocity;

        const float arriveRadius = params.arrive_radius;
        if (distanceToTarget < arriveRadius)
        {
        const float factor = distanceToTarget / arriveRadius;
            maxVelocity *= factor;
        }

        VelocityDesired.NormSafe();
        VelocityDesired *= maxVelocity;

        USVec2D accel = VelocityDesired - m_character->GetLinearVelocity();
        accel.NormSafe();

        m_Steering = (accel * params.max_acceleration);
        return m_Steering;
        


    }
    return USVec2D();
}


void ArriveSteering::DrawDebug() 
{

    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();


    //DesiredVelocity
    USVec2D pos = m_character->GetLoc();
    USVec2D delta = pos + VelocityDesired;

    gfxDevice.SetPenColor(1.0f, 0.0f, 0.f, 1.0f);
    MOAIDraw::DrawLine(pos.mX, pos.mY, delta.mX, delta.mY);


    //Acceleration
    delta = pos + m_Steering;
    gfxDevice.SetPenColor(1.f, 1.0f, 1.f, 1.0f);
    MOAIDraw::DrawLine(pos.mX, pos.mY, delta.mX, delta.mY);
}
