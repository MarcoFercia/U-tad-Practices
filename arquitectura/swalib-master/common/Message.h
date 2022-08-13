#pragma once
#include "vector2d.h"

class Entity;

class Message
{
public:
	Entity* Sender=nullptr;
	virtual void foo();
};

class NewParams :public Message
{
public:
	vec2 pos=vec2(0.f,0.f);
	vec2 vel = vec2(0.f, 0.f);
	float radius=0;
};

class CollisionMessage :public Message
{
public:
	
};

class EntColliisonMessage :public CollisionMessage
{
public:
	float change = -1.f;
};

class LimitWorldCollisionMessage :public CollisionMessage
{
public:
	vec2 newvel;
	
};


class NewPosMessage :public Message
{
public:
	vec2 newpos;
	vec2 newvel;
};

