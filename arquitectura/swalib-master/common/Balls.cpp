#pragma once

#include "Balls.h"

//#include "stdafx.h"
#include "sys.h"
#include "core.h"
//#include "vector2d.h"
#include "logica.h"


//extern Ball balls[];
extern const unsigned int NUM_BALLS;
extern LogicManager* MLogic;
 

GLuint Ball::GetGfx()
{
	return gfx;
}

vec2 Ball::GetPos()
{
	return pos;
}

vec2 Ball::GetVel()
{
	return vel;
}

float Ball::GetRadius()
{
	return radius;
}

float Ball::GetMaxSpeed()
{
	return MAX_BALL_SPEED;
}

void Ball::SetGfx(GLuint _gfx)
{
	gfx = _gfx;
}

void Ball::SetRadius(float _radius)
{
	radius = _radius;
}

void Ball::SetPos(vec2 _pos)
{
	
	pos = _pos;
}

void Ball::SetVel(vec2 _vel)
{
	vel = _vel;
}


void Ball::Slot(float _tick, int _i)
{

	Ball* pBall = MLogic->GetBalls();

	
		// New Pos.
		vec2 newpos = this->pos + (this->vel * (_tick*this->FACTORDELTA));
		
		// Collision detection.
		bool collision = false;
		int colliding_ball = -1;
		for (unsigned int j = 0; j < NUM_BALLS; j++) {
			if (_i != j) {
				float limit2 = (this->radius + (pBall + j)->GetRadius()) * (this->radius + (pBall + j)->GetRadius());
				if (vlen2(newpos - (pBall + j)->GetPos()) <= limit2) {
					collision = true;
					colliding_ball = j;
					break;
				}
			}
		}

		if (!collision) {
			this->pos = newpos;
		}
		else {
			// Rebound!
			this->vel = (this->vel * -1.f);
			(pBall + colliding_ball)->SetVel(((pBall + colliding_ball)->GetVel() * -1.f)) ;
		}

		// Rebound on margins.
		if ((this->pos.x > SCR_WIDTH) || (this->pos.x < 0))
		{
			this->vel.x *= -1.0;
		}

		if ((this->pos.y > SCR_HEIGHT) || (this->pos.y < 0))
		{
			this->vel.y *= -1.0;
		}
	
}