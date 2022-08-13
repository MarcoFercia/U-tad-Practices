
#include "Collider.h"
#include <cmath>
//#include <iostream>


float Clamp(float _value, float min, float max)
{
	if (_value >= min && _value <= max)
	{
		return _value;
	}
	if (_value < min)
	{
		return min;
	}
	else
	{
		return max;
	}
}



CircleCollider::CircleCollider(vec2 _CriclePos, float _radius):CriclePos(_CriclePos),radius(_radius)
{

}


RectCollider::RectCollider(vec2 _Rectpos, vec2 _RectSize):Rectpos(_Rectpos),RectSize(_RectSize)
{

}

PixelsCollider::PixelsCollider(uint8_t* _pixelbuffer, vec2 _PosPixel, vec2 _SizePixel):pixelbuffer(_pixelbuffer),PosPixel(_PosPixel),SizePixel(_SizePixel)
{

}


bool Collider::checkCircleCircle(const vec2& pos1, float radius1, const vec2& pos2, float radius2)
{
	vec2 DistanceAB = vec2(pos2.x - pos1.x, pos2.y - pos1.y);
	float lengthAB = DistanceAB.length(DistanceAB);

	float RadiusAB = radius1 + radius2;

	if (lengthAB <= RadiusAB)
	{
		return true;
	}
	return false;
}

bool Collider::checkCircleRect(const vec2& circlePos, float circleRadius, const vec2& rectPos, const vec2& rectSize)
{

	float nearpointx, nearpointy;

	nearpointx = circlePos.x;

	if (circlePos.x > rectPos.x + rectSize.x / 2)
	{
		nearpointx = rectPos.x + rectSize.x / 2;
	}
	else if (circlePos.x < rectPos.x - rectSize.x / 2)
	{
		nearpointx = rectPos.x - rectSize.x / 2;
	}

	nearpointy = circlePos.y;

	if (circlePos.y > rectPos.y + rectSize.y / 2)
	{
		nearpointy = rectPos.y + rectSize.y / 2;
	}
	else if (circlePos.y < rectPos.y - rectSize.y / 2)
	{
		nearpointy = rectPos.y - rectSize.y / 2;
	}


	

	
	vec2 NearPoint= vec2(nearpointx, nearpointy);
	vec2 Distance = vec2(circlePos.x - NearPoint.x,circlePos.y-NearPoint.y);
	

	float lessDistance = Distance.length(Distance);
	
	if (lessDistance < circleRadius)
	{
		return true;
	}

	return false;
}

bool Collider::checkRectRect(const vec2& rectPos1, const vec2& rectSize1, const vec2& rectPos2, const vec2& rectSize2)
{	
	if (rectPos1.x + rectSize1.x / 2 > rectPos2.x - rectSize2.x / 2 &&
		rectPos1.x - rectSize1.x / 2 < rectPos2.x + rectSize2.x / 2 &&
		rectPos1.y + rectSize1.y / 2 > rectPos2.y - rectSize2.y / 2 &&
		rectPos1.y - rectSize1.y / 2 < rectPos2.y + rectSize2.y / 2)
	{
		return true;
	}
	return false;
}

bool Collider::checkCirclePixels(const vec2& circlePos, float circleRadius, const vec2& pixelsPos, const vec2& pixelsSize, const uint8_t* pixels)
{
	

	if (checkCircleRect(circlePos, circleRadius, pixelsPos, pixelsSize))
	{


		vec2 positionOriginPixel = vec2(pixelsPos.x - pixelsSize.x / 2, pixelsPos.y - pixelsSize.y / 2);

        float RightCol = std::fminf(pixelsPos.x + pixelsSize.x / 2, circlePos.x + circleRadius);
        float LeftCol = std::fmaxf(pixelsPos.x - pixelsSize.x / 2, circlePos.x - circleRadius);
        float DownCol = std::fminf(pixelsPos.y + pixelsSize.y / 2, circlePos.y + circleRadius);
        float UpCol = std::fmaxf(pixelsPos.y - pixelsSize.y / 2, circlePos.y - circleRadius);



		for (int y = UpCol; y < DownCol; ++y)
		{
			for (int x = LeftCol; x < RightCol; x++)
			{

                vec2 distanceOrigin = vec2(x - positionOriginPixel.x, y - positionOriginPixel.y);


                int ArrayPixelPos = ((distanceOrigin.y * pixelsSize.x) + distanceOrigin.x) * 4 + 3;

                if (pixels[ArrayPixelPos] != 0)
                {
					vec2 TempPixelPos = vec2(x, y);
					vec2 DistanceCirclePixel = vec2(circlePos.x - TempPixelPos.x,circlePos.y-TempPixelPos.y);
					float tempDistance = DistanceCirclePixel.length(DistanceCirclePixel);

					if (tempDistance < circleRadius)
					{
						return true;
					}
                }

			}
		}


	}
	return false;
}

bool Collider::checkPixelsPixels(const vec2& pixelsPos1, const vec2& pixelsSize1, const uint8_t* pixels1, const vec2& pixelsPos2, const vec2& pixelsSize2, const uint8_t* pixels2)
{

	if (checkRectRect(pixelsPos1, pixelsSize1, pixelsPos2, pixelsSize2))
	{


		vec2 positionOriginPixel1 = vec2(pixelsPos1.x - pixelsSize1.x / 2, pixelsPos1.y - pixelsSize1.y / 2);
		vec2 positionOriginPixel2 = vec2(pixelsPos2.x - pixelsSize2.x / 2, pixelsPos2.y - pixelsSize2.y / 2);

		float RightCol = std::fminf(pixelsPos1.x + pixelsSize1.x / 2, pixelsPos2.x + pixelsSize2.x / 2);
		float LeftCol = std::fmaxf(pixelsPos1.x - pixelsSize1.x / 2, pixelsPos2.x - pixelsSize2.x / 2);
		float DownCol = std::fminf(pixelsPos1.y + pixelsSize1.y / 2, pixelsPos2.y + pixelsSize2.y / 2);
		float UpCol = std::fmaxf(pixelsPos1.y - pixelsSize1.y / 2, pixelsPos2.y - pixelsSize2.y / 2);



		for (int y = UpCol; y < DownCol; ++y)
		{
			for (int x = LeftCol; x < RightCol; x++)
			{


				vec2 distanceOrigin1 = vec2(x - positionOriginPixel1.x, y - positionOriginPixel1.y);
				vec2 distanceOrigin2 = vec2(x - positionOriginPixel2.x, y - positionOriginPixel2.y);

				int ArrayPixelPos1 = ((distanceOrigin1.y * pixelsSize1.x) + distanceOrigin1.x) * 4 + 3;

				if (pixels1[ArrayPixelPos1] != 0)
				{
					int ArrayPixelPos2 = ((distanceOrigin2.y * pixelsSize2.x ) + distanceOrigin2.x) * 4 + 3;
					
					if (pixels2[ArrayPixelPos2] != 0)
					{
						return true;
					}
				}

			}
		}
	}



	return false;





	
}

bool Collider::checkPixelsRect(const vec2& pixelsPos, const vec2& pixelsSize, const uint8_t* pixels, const vec2& rectPos, const vec2& rectSize)
{

	if (checkRectRect(rectPos, rectSize, pixelsPos, pixelsSize))
	{
		

		vec2 positionOriginPixel = vec2(pixelsPos.x - pixelsSize.x/2, pixelsPos.y - pixelsSize.y/2);


		float RightCol = std::fminf(pixelsPos.x + pixelsSize.x / 2, rectPos.x + rectSize.x / 2);
		float LeftCol = std::fmaxf(pixelsPos.x - pixelsSize.x / 2, rectPos.x - rectSize.x / 2);
		float DownCol = std::fminf(pixelsPos.y + pixelsSize.y / 2, rectPos.y + rectSize.y / 2);
		float UpCol = std::fmaxf(pixelsPos.y - pixelsSize.y / 2, rectPos.y - rectSize.y / 2);



        for (int y = UpCol; y < DownCol; ++y)
        {
            for (int x = LeftCol; x < RightCol; x++)
            {


                vec2 distanceOrigin = vec2(x - positionOriginPixel.x, y - positionOriginPixel.y);

                int ArrayPixelPos = ((distanceOrigin.y * pixelsSize.x / 2 * 2) + distanceOrigin.x) * 4 + 3;

                if (pixels[ArrayPixelPos] != 0)
                {
                    return true;
                }

            }
        }

        

	}


	
	return false;




	
}






bool CircleCollider::collides(const Collider& other)const
{
	return other.collides(this->CriclePos, this->radius);
}

bool CircleCollider::collides(const vec2& circlePos, float circleRadius)const
{
	return Collider::checkCircleCircle(this->CriclePos, this->radius, circlePos, circleRadius);
}

bool CircleCollider::collides(const vec2& rectPos, const vec2& rectSize)const
{
	return Collider::checkCircleRect(this->CriclePos, this->radius, rectPos, rectSize);
}

bool CircleCollider::collides(const vec2& pixelsPos, const vec2& pixelsSize, const uint8_t* pixels)const
{
	return Collider::checkCirclePixels(this->CriclePos, this->radius, pixelsPos, pixelsSize, pixels);
}



bool RectCollider::collides(const Collider& other)const
{
	return other.collides(this->Rectpos, this->RectSize);
}

bool RectCollider::collides(const vec2& circlePos, float circleRadius)const
{
	return Collider::checkCircleRect(circlePos, circleRadius, this->Rectpos, this->RectSize);
}

bool RectCollider::collides(const vec2& rectPos, const vec2& rectSize)const
{
	return Collider::checkRectRect(this->Rectpos, this->RectSize, rectPos, rectSize);
}

bool RectCollider::collides(const vec2& pixelsPos, const vec2& pixelsSize, const uint8_t* pixels)const
{
	return Collider::checkPixelsRect(pixelsPos, pixelsSize, pixels, this->Rectpos, this->RectSize);
}



bool PixelsCollider::collides(const Collider& other)const
{
	return 	other.collides(this->PosPixel, this->SizePixel, this->pixelbuffer);
}

bool PixelsCollider::collides(const vec2& circlePos, float circleRadius)const
{
	return Collider::checkCirclePixels(circlePos, circleRadius, this->PosPixel, this->SizePixel, this->pixelbuffer);
}

bool PixelsCollider::collides(const vec2& rectPos, const vec2& rectSize) const 
{
	return Collider::checkPixelsRect(this->PosPixel, this->SizePixel, this->pixelbuffer, rectPos, rectSize);
}

bool PixelsCollider::collides(const vec2& pixelsPos, const vec2& pixelsSize, const uint8_t* pixels) const
{
	return Collider::checkPixelsPixels(this->PosPixel, this->SizePixel, this->pixelbuffer, pixelsPos, pixelsSize, pixels);
}



void CircleCollider::setRadius(float _newradius)
{
	radius = _newradius;
}

void CircleCollider::setPos(vec2 _newpos)
{
	CriclePos = _newpos;
}

void RectCollider::setPos(vec2 _newpos)
{
	Rectpos = _newpos;
}

void RectCollider::setSize(vec2 _newsize)
{
	RectSize = _newsize;
}

void PixelsCollider::setSize(vec2 _newsize)
{
	SizePixel = _newsize;
}

void PixelsCollider::setPos(vec2 _newpos)
{
	PosPixel = _newpos;
}