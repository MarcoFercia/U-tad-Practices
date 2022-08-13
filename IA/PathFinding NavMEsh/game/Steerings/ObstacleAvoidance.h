#pragma once


#include "Steering.h"
#include "uslscore/USVec2D.h"


class ObstacleAvoidance : public Steering
{
public:
 
      ObstacleAvoidance(Character* _character) : Steering(_character) {};
      ~ObstacleAvoidance();
      
      ResultSteering& GetSteering(const USVec2D& _target) override;
      void DrawDebug() override;

private:

    USVec2D mProjLocation;
};