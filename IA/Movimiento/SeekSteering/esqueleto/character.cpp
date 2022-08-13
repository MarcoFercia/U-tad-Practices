#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>
#include <params.h>
#include <SeekSteering.h>


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
	mSteering = new SeekSteering(this);
}

void Character::OnStop()
{
	delete mSteering;
}

void Character::OnUpdate(float step)
{



	USVec2D steering = mSteering->GetSteering();

	mLinearVelocity += steering * step;

	USVec2D pos = GetLoc();

	pos += mLinearVelocity * step;

	SetLoc(pos);


}

void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 1.0f);

	MOAIDraw::DrawPoint(mParams.targetPosition);

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
	