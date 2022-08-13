#include <stdafx.h>
#include "character.h"
#include "Steerings/PathFollowing.h"
#include "Steerings/AlignToMovement.h"
#include "params.h"

Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
	RTTI_EXTEND(MOAIEntity2D)
	RTTI_END

	steerings.push_back(new PathFollowing(this));
	steerings.push_back(new AlignToMovement(this));
	pathfinder = new Pathfinder();
	ReadParams("params.xml", params);

}

Character::~Character()
{

}

void Character::OnStart()
{

}

void Character::OnStop()
{

}

void Character::OnUpdate(float step)
{
    params.char_radius;
        if (pathfinder->IsPathCompleted())
        {

            ResultSteering steeringResult;
            for (Steering* steering : steerings)
            {
                steeringResult += steering->GetSteering(USVec2D());
            }

            mLinearVelocity += steeringResult.linear * step;
            //mAngularVelocity += steeringResult.angular * step;
            SetLoc(mLinearVelocity * step + GetLoc());
           // SetRot(mAngularVelocity * step + GetRot());
        }
        else
        {
            pathfinder->PathfindStep();
        }
	
}

void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);

	//MOAIDraw::DrawPoint(0.0f, 0.0f);
    pathfinder->DrawDebug();

    for (Steering* it : steerings)
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
        {"setStartPosition", _setStartPosition},
        {"setEndPosition", _setEndPosition},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(2, 0.0f);
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
	
int Character::_setStartPosition(lua_State* L)
{
    MOAI_LUA_SETUP(Character, "U")

    float x = state.GetValue<float>(2, 0.0f);
    float y = state.GetValue<float>(3, 0.0f);
    self->GetPathfinder()->SetStartPosition(x, y);
    //self->SetLoc(USVec3D(x, y, 0.f));

    return 0;
}

int Character::_setEndPosition(lua_State* L)
{
    MOAI_LUA_SETUP(Character, "U")

    float x = state.GetValue<float>(2, 0.0f);
    float y = state.GetValue<float>(3, 0.0f);
    self->GetPathfinder()->SetEndPosition(x, y);
      self->SetLoc(USVec3D(x, y, 0.f));

    return 0;
}
