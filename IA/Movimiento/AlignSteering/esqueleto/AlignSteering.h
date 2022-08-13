#pragma once



#include "uslscore/USVec2D.h"

//#include "params.h"
class Character;

class AlignSteering 
{

public:

	explicit AlignSteering(Character* _character);

public:
	  float GetSteering();

	

	  void DrawDebug();



     static void NormalizeAngle(float& angleInRadians);
     static float ToRadians(float angleInDegrees);
     static float ToDegrees(float angleInRadians);

	 Character* m_character;
	 

	 float VelocityDesired;
	 float steering;


};