#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <moaicore/MOAIEntity2D.h>
#include "params.h"
#include "pathfinding/pathfinder.h"
#include "Steerings/Steering.h"

class Character: public MOAIEntity2D
{
public:
    DECL_LUA_FACTORY(Character)
protected:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnUpdate(float step);
public:
	virtual void DrawDebug();

	Character();
	~Character();
	
	void SetLinearVelocity(float x, float y) { mLinearVelocity.mX = x; mLinearVelocity.mY = y;}
	void SetAngularVelocity(float angle) { mAngularVelocity = angle;}
	
	USVec2D GetLinearVelocity() const { return mLinearVelocity;}
	float GetAngularVelocity() const { return mAngularVelocity;}

    const Params& GetParams() const { return params; }
    Pathfinder* GetPathfinder() const { return pathfinder; }

private:
	USVec2D mLinearVelocity;
	float mAngularVelocity;
	

	Params params;
	Pathfinder* pathfinder;
	std::vector<Steering*> steerings;
	
	// Lua configuration
public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
	static int _setLinearVel(lua_State* L);
	static int _setAngularVel(lua_State* L);
    static int _setStartPosition(lua_State* L);
    static int _setEndPosition(lua_State* L);
};

#endif