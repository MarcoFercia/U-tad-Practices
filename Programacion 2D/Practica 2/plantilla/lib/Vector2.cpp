#pragma once

#include "glfw3.h"
#include <math.h>
#include "Vector2.h"


vec2::vec2(float _x, float _y) : x(_x), y(_y)
{
}

vec2::~vec2()
{
}

vec2 vec2::operator+ (const vec2& _ref)
{
	vec2 vc;
	vc.x = vc.x + _ref.x;
	vc.y = vc.y + _ref.y;
	return vc;
}

vec2 vec2::operator -(const vec2& _ref)
{
	vec2 vc;
	vc.x = vc.x - _ref.x;
	vc.y = vc.y - _ref.y;
	return vc;
}

vec2 vec2::operator *(const vec2& _ref)
{
	vec2 vc;
	vc.x = vc.x * _ref.x;
	vc.y = vc.y * _ref.y;
	return vc;
}

vec2 vec2::operator /(const vec2& _ref)
{
	vec2 vc;
	vc.x = vc.x / _ref.x;
	vc.y = vc.y / _ref.y;
	return vc;
}

vec2 vec2::operator *(float _ref)
{
	vec2 vc;
	vc.x = vc.x * _ref;
	vc.y = vc.y * _ref;
	return vc;
}

vec2 vec2::operator /(float _ref)
{
	vec2 vc;
	vc.x = vc.x / _ref;
	vc.y = vc.y / _ref;
	return vc;
}

vec2 vec2::abst(vec2& _ref)
{
	vec2 vc;
	vc.x = fabs(_ref.x);
	vc.y = fabs(_ref.y);
	return vc;

}

float vec2::length(vec2& _ref)
{
	return sqrt((_ref.x * _ref.x) + (_ref.y * _ref.y));
}

vec2 vec2::normal(vec2& _ref)
{
	vec2 vc;
	float temp = length(_ref);

	vc.x = _ref.x / temp;
	vc.y = _ref.y / temp;
	return vc;

}

float vec2::dotp(vec2& _refa, vec2& _refb)
{
	return ((_refa.x * _refb.x) + (_refa.y * _refb.y));
}


float vec2::angle(const vec2& other) const
{
	float x, y;
	x = other.x - this->x;
	y = other.y - this->y;

	if (x == 0)
	{
		return ((acos(1 / y))* 57.2957795);
	}
	else if (y == 0)
	{
		return ((asin(1 / x))* 57.2957795);
	}
	else
	{
		return ((atan(x / y)) * 57.2957795);
	}
}

float vec2::distance(const vec2& other) const
{;
	vec2 Distancia(this->x-(other.x/2),this->y-(other.y/2));
	return Distancia.length(Distancia);
}