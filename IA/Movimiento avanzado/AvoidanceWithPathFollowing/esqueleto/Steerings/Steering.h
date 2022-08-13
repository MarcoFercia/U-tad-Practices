#pragma once


//#include <character.h>
//#include <params.h>
#include <uslscore/USVec2D.h>

class Character;

struct ResultSteering
{
	USVec2D linear;
	float angular;

	ResultSteering(const USVec2D& _linear = USVec2D(0.f, 0.f), float _angular = 0.f) : linear(_linear),angular(_angular)
	{}

    ResultSteering operator+(const ResultSteering& other)
    {
        ResultSteering result;
        result.linear = linear + other.linear;
        result.angular = angular + other.angular;
        return result;
    }

    void operator+=(const ResultSteering& other)
    {
        linear += other.linear;
        angular += other.angular;
    }
};




class Steering
{

public:
    Steering(Character* _character) : mCharacter(_character) 
    {}

    ~Steering();
    


     
    virtual ResultSteering& GetSteering(const USVec2D& _target) { return mSteering; }
    virtual ResultSteering& GetSteering(float _target) { return mSteering; }
	 virtual void DrawDebug() = 0;
    // void SetDelegate(Steering* _steering) { m_delegate = _steering; }

     //ResultSteering CallDelegate() const;


protected:

    //Steering* m_delegate = nullptr;
    ResultSteering mSteering;
    //USVec2D VelocityDesired;
    Character* mCharacter = nullptr;
	
};