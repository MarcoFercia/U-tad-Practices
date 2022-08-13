#pragma once
#include "Vector2.h"
#include <cstdint>


class Collider
{

public:

	virtual bool collides(const Collider& other) const = 0;
	virtual bool collides(const vec2& circlePos, float circleRadius) const = 0;
	virtual bool collides(const vec2& rectPos, const vec2& rectSize) const = 0;
	virtual bool collides(const vec2& pixelsPos, const vec2& pixelsSize, const uint8_t* pixels) const = 0;



	static bool checkCircleCircle(const vec2& pos1, float radius1,const vec2& pos2, float radius2);
	static bool checkCircleRect(const vec2& circlePos, float circleRadius,	const vec2& rectPos, const vec2& rectSize);
	static bool checkRectRect(const vec2& rectPos1, const vec2& rectSize1,const vec2& rectPos2, const vec2& rectSize2);
	static bool checkCirclePixels(const vec2& circlePos, float circleRadius,const vec2& pixelsPos, const vec2& pixelsSize, const uint8_t* pixels);
	static bool checkPixelsPixels(const vec2& pixelsPos1, const vec2& pixelsSize1, const uint8_t* pixels1,const vec2& pixelsPos2, const vec2& pixelsSize2, const uint8_t* pixels2);
	static bool checkPixelsRect(const vec2& pixelsPos, const vec2& pixelsSize, const uint8_t* pixels,const vec2& rectPos, const vec2& rectSize);

	virtual void setPos(vec2 _newpos) {};
	virtual void setSize(vec2 _newsize) {};
	virtual void setRadius(float _newradius) {};

	virtual vec2 GetPos () = 0;
	virtual vec2 GetSize() { return vec2(0.f, 0.f); }
	virtual float GetRadius() { return 0.f; }
	virtual uint8_t* GetPixel() { return nullptr; }

};

class CircleCollider : public Collider
{

private:
    vec2 CriclePos;
    float radius;
public:

	virtual void setPos( vec2 _newpos) override;
	virtual void setRadius(float _newradius) override;

	virtual bool collides(const Collider& other) const ;
	virtual bool collides(const vec2& circlePos, float circleRadius)const;
	virtual bool collides(const vec2& rectPos, const vec2& rectSize)const;
	virtual bool collides(const vec2& pixelsPos, const vec2& pixelsSize, const uint8_t* pixels)const;

	CircleCollider(vec2 _CriclePos,	float _radius);

	virtual vec2 GetPos()override { return CriclePos; }
	virtual float GetRadius() override { return radius; }

};

class RectCollider : public Collider
{
private:
	vec2 Rectpos;
	vec2 RectSize;
public:

	virtual void setPos( vec2 _newpos) override;
	virtual void setSize(vec2 _newsize) override;

	virtual bool collides(const Collider& other)const;
	virtual bool collides(const vec2& circlePos, float circleRadius)const;
	virtual bool collides(const vec2& rectPos, const vec2& rectSize) const;
	virtual bool collides(const vec2& pixelsPos, const vec2& pixelsSize, const uint8_t* pixels)const;

	virtual vec2 GetPos() override { return Rectpos; }
	virtual vec2 GetSize() override { return RectSize; }

	RectCollider(vec2 _Rectpos, vec2 _RectSize);

};

class PixelsCollider : public Collider
{
private:

	uint8_t* pixelbuffer;
	vec2 PosPixel;
	vec2 SizePixel;
public:

	virtual void setPos(vec2 _newpos) override;
	virtual void setSize(vec2 _newsize) override;

	virtual bool collides(const Collider& other) const;
	virtual bool collides(const vec2& circlePos, float circleRadius) const;
	virtual bool collides(const vec2& rectPos, const vec2& rectSize) const;
	virtual bool collides(const vec2& pixelsPos, const vec2& pixelsSize, const uint8_t* pixels) const;

	virtual vec2 GetPos()override { return PosPixel; }
	virtual vec2 GetSize() override { return SizePixel; }
	virtual uint8_t* GetPixel() override {return pixelbuffer;}

	PixelsCollider(uint8_t* _pixelbuffer, vec2 _PosPixel, vec2 _SizePixel);


};