#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>
#include <params.h>
#include <SeekSteering.h>
#include "ArriveSteering.h"
#include "AlignSteering.h"


Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
		RTTI_EXTEND(MOAIEntity2D)
	RTTI_END
		
}

Character::~Character()
{
	
}

void Character::OnStart()
{
    ReadParams("params.xml", mParams);
	mAlignSteering = new AlignSteering(this);
}

void Character::OnStop()
{
	delete mSteering;
}

void Character::OnUpdate(float step)
{

	MOAIEntity2D::OnUpdate(step);

	float steering = mAlignSteering->GetSteering();
	mAngularVelocity += steering * step;
	printf("Sterring -->  %f\n", steering);

	float rotaiton = GetRot();
	rotaiton += mAngularVelocity * step;
	SetRot(rotaiton);


}

void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 1.0f);

	//MOAIDraw::DrawPoint(mParams.targetPosition);


	const USVec2D pos = GetLoc();


//     // Dest radius
//     MOAIDraw::DrawEllipseOutline(mParams.targetPosition.mX, mParams.targetPosition.mY, mParams.dest_radius, mParams.dest_radius, 10);
// 
//     // Arrive radius
//     MOAIDraw::DrawEllipseOutline(mParams.targetPosition.mX, mParams.targetPosition.mY, mParams.arrive_radius, mParams.arrive_radius, 10);
    


	
	gfxDevice.SetPenColor(0.7f, 0.2f, 0.2f, 1.f);
    // Draw target rotation
    float targetRotation = mAlignSteering->ToRadians(mParams.target_rotation);
	mAlignSteering->NormalizeAngle(targetRotation);
    USVec2D delta = USVec2D(cosf(targetRotation), sinf(targetRotation)) * 50.f + GetLoc();
    MOAIDraw::DrawLine(GetLoc().mX, GetLoc().mY, delta.mX, delta.mY);

    float arriveRadius = mAlignSteering->ToRadians(mParams.angular_arrive_radius);
    delta = USVec2D(cosf(targetRotation + arriveRadius), sinf(targetRotation + arriveRadius)) * 50.f + GetLoc();
    MOAIDraw::DrawLine(GetLoc().mX, GetLoc().mY, delta.mX, delta.mY);
    delta = USVec2D(cosf(targetRotation - arriveRadius), sinf(targetRotation - arriveRadius)) * 50.f + GetLoc();
    MOAIDraw::DrawLine(GetLoc().mX, GetLoc().mY, delta.mX, delta.mY);

    // Show current rotation
    gfxDevice.SetPenColor(0.5f, 1.f, 0.f, 1.f);
    float currentRotation = mAlignSteering->ToRadians(GetRot());
    delta = USVec2D(cosf(currentRotation), sinf(currentRotation)) * 50.f + GetLoc();
    MOAIDraw::DrawLine(GetLoc().mX, GetLoc().mY, delta.mX, delta.mY);



	mAlignSteering->DrawDebug();
}





// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);
	
	luaL_Reg regTable [] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetLinearVelocity(pX, pY);
	return 0;	
}

int Character::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}
	