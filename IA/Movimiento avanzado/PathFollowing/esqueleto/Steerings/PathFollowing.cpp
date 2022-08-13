#include <stdafx.h>
#include "PathFollowing.h"

#include <character.h>
#include <params.h>
#include "Path.h"




PathFollowing::PathFollowing(Character* _character) : Steering(_character)
{

}

PathFollowing::~PathFollowing()
{

}

void PathFollowing::OnUpdate(float _deltatime)
{

    USVec2D pos = mCharacter->GetLoc();
    USVec2D vel = mCharacter->GetLinearVelocity();
    mProjection = pos + vel * mCharacter->GetParams().time_ahead;

    
    Path::PointSegment Segment = mCharacter->GetPath().GetClosestPoint(mProjection);
    mClosest =Segment.SegmentPoint;
    float LookAhead = mCharacter->GetParams().look_ahead;
    mTarget = mCharacter->GetPath().GetPointAhead(Segment, LookAhead);
    mCharacter->SetTarget(mTarget);

}

ResultSteering PathFollowing::GetSteering()
{
    return mSteering;
}

void PathFollowing::DrawDebug()
{
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

    gfxDevice.SetPenColor(0.f, 0.1f, 0.f, 1.f);
    MOAIDraw::DrawEllipseFill(mProjection.mX, mProjection.mY, 5.f, 5.f, 10);
    MOAIDraw::DrawLine(USVec2D(mCharacter->GetLoc()), mProjection);

    gfxDevice.SetPenColor(0.f, 0.f, 0.1f, 1.f);
    MOAIDraw::DrawEllipseFill(mClosest.mX, mClosest.mY, 5.f, 5.f, 10);
    MOAIDraw::DrawLine(mProjection, mClosest);

    gfxDevice.SetPenColor(0.f, 0.5f, 0.5f, 1.f);
    MOAIDraw::DrawEllipseFill(mTarget.mX, mTarget.mY, 5.f, 5.f, 10);
    MOAIDraw::DrawLine(USVec2D(mCharacter->GetLoc()), mTarget);
}
