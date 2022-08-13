#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>
#include <params.h>
#include "Steerings/ArriveSteering.h"
#include "Steerings/AlignToMovement.h"
#include <xlocinfo>
#include "Steerings/Steering.h"
#include "Steerings/PathFollowing.h"
#include "Steerings/ObstacleAvoidance.h"



Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
		RTTI_EXTEND(MOAIEntity2D)
		RTTI_END


		mSteerings.push_back(new ObstacleAvoidance(this));
		//mSteerings.push_back(new ArriveSteering(this));
		//mSteerings.push_back(new AlignToMovement(this));

		
}

Character::~Character()
{

	for (Steering* it : mSteerings)
	{
		delete it;
	}

	mSteerings.clear();
}

void Character::OnStart()
{
    ReadParams("params.xml", mParams);
	mPath.Load("path.xml");
	Obstacle::LoadFromFile(mObstacles, "obstacles.xml");
	//mSteering = new ArriveSteering(this);
	//mSteering->SetDelegate(new AlignToMovement(this));
}

void Character::OnStop()
{
 
}

void Character::OnUpdate(float step)
{

	MOAIEntity2D::OnUpdate(step);

	ResultSteering steeringResult;

	for (Steering* it : mSteerings)
	{
		if (it)
		{
            //it->OnUpdate(step);
            steeringResult += it->GetSteering(USVec2D());
		}
	
	}

	mLinearVelocity += steeringResult.linear * step;
	mAngularVelocity += steeringResult.angular * step;
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
	


    gfxDevice.SetPenColor(0.7f, 0.2f, 0.2f, 1.f);
    //mPath.DrawDebug();

	for (Steering* it : mSteerings)
		{
			it->DrawDebug();
		}
		

	for (Obstacle* it : mObstacles)
	{
		it->DrawDebug();
	}

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




