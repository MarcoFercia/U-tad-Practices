#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>
#include <params.h>
#include <SeekSteering.h>
#include "ArriveSteering.h"
#include "AlignSteering.h"
#include "AlignToMovement.h"


Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
		RTTI_EXTEND(MOAIEntity2D)
	RTTI_END
		
}

Character::~Character()
{
	delete mSteering;
}

void Character::OnStart()
{
    ReadParams("params.xml", mParams);
	mSteering = new ArriveSteering(this);
	mSteering->SetDelegate(new AlignToMovement(this));
}

void Character::OnStop()
{
 
}

void Character::OnUpdate(float step)
{

	MOAIEntity2D::OnUpdate(step);

	ResultSteering steering = mSteering->GetSteering();
	mLinearVelocity += steering.linear * step;
	mAngularVelocity += steering.angular * step;
	SetLoc(GetLoc() + mLinearVelocity * step);
	SetRot(GetRot() + mAngularVelocity * step);

}

void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 1.0f);

	MOAIDraw::DrawPoint(mParams.targetPosition);



    MOAIDraw::DrawPoint(mParams.targetPosition.mX, mParams.targetPosition.mY);
    // Arrive radius
    MOAIDraw::DrawEllipseOutline(mParams.targetPosition.mX, mParams.targetPosition.mY, mParams.arrive_radius,
        mParams.arrive_radius, 10);
    // Dest radius
    MOAIDraw::DrawEllipseOutline(mParams.targetPosition.mX, mParams.targetPosition.mY, mParams.dest_radius,
        mParams.dest_radius, 10);
	



	mSteering->DrawDebug();
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




