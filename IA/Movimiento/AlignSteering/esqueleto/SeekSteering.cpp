#include <stdafx.h>
#include "SeekSteering.h"

#include <character.h>
#include <params.h>


SeekSteering::SeekSteering(Character* _character) : m_character(_character), m_target()
{

}

USVec2D SeekSteering::GetSteering()
{
    if (m_character)
    {
        m_target = m_character->GetParams().targetPosition;
        VelocityDesired = m_target - m_character->GetLoc();
        USVec2D accel = VelocityDesired - m_character->GetLinearVelocity();
        accel.NormSafe();
        Acceleration = accel * m_character->GetParams().max_acceleration;
        return Acceleration;

    }
    return USVec2D();
}

void SeekSteering::SetTarget(const USVec2D& _target)
{
    m_target = _target;
}

void SeekSteering::DrawDebug()
{

    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

  
    //DesiredVelocity
    USVec2D pos = m_character->GetLoc();
    USVec2D delta = pos + VelocityDesired;

    gfxDevice.SetPenColor(1.0f, 0.0f, 0.2f, 1.0f);
    MOAIDraw::DrawLine(pos.mX, pos.mY, delta.mX, delta.mY);

   
    //Acceleration
    delta = pos + Acceleration;
    gfxDevice.SetPenColor(0.f, 1.0f, 0.2f, 1.0f);
    MOAIDraw::DrawLine(pos.mX,pos.mY,delta.mX,delta.mY);
}
