#pragma once
#include"vector2d.h"
#include "stdafx.h"


#include<vector>

class Entity;
class Message;

class Component
{

	
public:
	virtual void Slot(float elapsed) = 0;
	Entity* m_Owner=nullptr;
	virtual void ReciveMessage(Message* _msg);
	
};


class Entity
{
	
	std::vector<Component*> m_Components;
public:
	virtual void Slot(float _elapsed);
	void AddComponent(Component* _pComponent);
	void SendMessages(Message* _msg);
	int tier = 0;
	template <class T>
	T* FindComponent();


	enum class Identifier{None=0,Player=1, Enemy=2, Bullet=3};
	~Entity();

	 void Call();
	 void Call2();
	Identifier type=Identifier::None;
	bool isActive = false;
};

class CollisionComponent : public Component
{

public:
	virtual void Slot(float elapsed) override;
	bool collision;
	CollisionComponent(Entity* _owner,vec2 _pos,float _radius,vec2 _vel);
	virtual void ReciveMessage(Message* _msg) override;

	vec2 pos;
	float radius;
	vec2 vel;
	
};



class MovementComponent : public Component
{
public:
	vec2 pos;
	vec2 vel;
	bool Collision = false;
	MovementComponent(Entity* _owner, vec2 _pos, vec2 _vel);
	virtual void ReciveMessage(Message* _msg) override;

private:
	virtual void Slot(float elapsed) override;

};

class RenderComponent : public Component
{
public:
	GLuint gfx;
	vec2 pos;
	float radius;
	RenderComponent(Entity* _owner, vec2 _pos, float _radius, GLuint _gfx);
	void CallSlot();
	virtual void ReciveMessage(Message* _msg) override;

private:
	virtual void Slot (float elapsed) override;

};

class PlayerControllerComponent : public Component
{

public:
	enum class Actions {None=0,MRight=1,MLeft=2,Fire=3};
	
	virtual void Slot(float elapsed) override;
	virtual void ReciveMessage(Message* _msg) override;
	void InputManager();
	PlayerControllerComponent(Entity* _owner, vec2 _pos, vec2 _vel);

	int hp = 3;
	vec2 pos;
	vec2 vel;
	Actions NextAction = Actions::None;

};



