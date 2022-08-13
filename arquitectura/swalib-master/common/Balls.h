#pragma once

#include"vector2d.h"
#include "stdafx.h"

//class vec2;
//typedef GLuint;


class Ball	// Info Ball
{
private:
	vec2   pos;	// Position.
	vec2   vel;	// Velocity.
	GLuint gfx;	// OpenGL for id. for visualization purposes. 
	float  radius;	// Radius.
	const float MAX_BALL_SPEED = 8.f;
	const float FACTORDELTA = 25.f;
	
public:

	void SetPos(vec2 _pos);
	void SetVel(vec2 _vel);
	void SetGfx(GLuint _gfx);
	void SetRadius(float _radius);
	GLuint GetGfx();
	//void SetSpeed();
	vec2 GetPos();
	vec2 GetVel();
	float GetRadius();
	float GetMaxSpeed();


	void Slot(float _tick, int _i);

	Ball::Ball() :
		pos(0.f, 0.f),
		vel(0.f, 0.f),
		gfx(0),
		radius(0.f)
	{}

};






 

