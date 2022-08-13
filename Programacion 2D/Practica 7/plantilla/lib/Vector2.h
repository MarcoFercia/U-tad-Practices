#pragma once

class vec2
{
public:

	vec2(float _x = 0.f, float _y = 0.f);
	~vec2();


	vec2 operator+ (const vec2& _ref);
				
	vec2 operator -(const vec2& _ref);

	vec2 operator *(const vec2& _ref);

	vec2 operator /(const vec2& _ref);

	vec2 operator *(float _ref);

	vec2 operator /(float _ref);
	
	vec2 abst(vec2& _ref);

	float length(vec2& _ref);

	vec2 normal(vec2& _ref);
	
	float dotp(vec2& _refa, vec2& _refb);

	float angle(const vec2& other) const;

	float distance(const vec2& other) const;

	float x;
	float y;



	
	
};

