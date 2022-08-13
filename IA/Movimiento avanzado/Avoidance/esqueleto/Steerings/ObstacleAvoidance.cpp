#include <stdafx.h>
#include "ObstacleAvoidance.h"
#include <character.h>
#include <params.h>
#include "Obstacles.h"


ObstacleAvoidance::~ObstacleAvoidance()
{

}

ResultSteering& ObstacleAvoidance::GetSteering(const USVec2D& _target)
{
    if (mCharacter)
    {
        mSteering = ResultSteering();
        std::vector<Obstacle*> obstacles = mCharacter->GetObstacles();
        float lookAhead = mCharacter->GetParams().obstacle_look_ahead;
        float charRadius = mCharacter->GetParams().char_radius;
        USVec2D characterDirection = mCharacter->GetLinearVelocity();
        characterDirection.NormSafe();

        for (const Obstacle* it : obstacles)
        {
            USVec2D LocalLocationObstacle = it->GetPosition() - mCharacter->GetLoc();
            float proj = LocalLocationObstacle.Dot(characterDirection);
            if (proj > 0.f)
            {
                if (proj > lookAhead)
                {
                    mProjLocation = mCharacter->GetLoc() + characterDirection * lookAhead;
                }
                else
                {
                    mProjLocation = mCharacter->GetLoc() + characterDirection * proj;
                }

                USVec2D difference = it->GetPosition() - mProjLocation;
                float distSquare = difference.LengthSquared();
                float limitCollisionSquared = it->GetRadius() + charRadius;
                limitCollisionSquared *= limitCollisionSquared;
                if (distSquare < limitCollisionSquared)
                {
                    USVec2D Product = LocalLocationObstacle;
                    float result = Product.Cross(mProjLocation);
                    if (result >= 0.f)
                    {
                        Product.Rotate90Clockwise();
                    }
                    else
                    {
                        Product.Rotate90Anticlockwise();
                    }
                    Product.NormSafe();
                    Product.Scale(mCharacter->GetParams().max_acceleration);
                    mSteering.linear += Product;
                }
            }
        
        }       
    }
    else
    {
        mSteering = ResultSteering();
    }
    return mSteering;
}

void ObstacleAvoidance::DrawDebug()
{
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

    gfxDevice.SetPenColor(0.f, 0.7f, 0.5f, 1.f);
    MOAIDraw::DrawEllipseOutline(mProjLocation.mX, mProjLocation.mY, mCharacter->GetParams().char_radius,
        mCharacter->GetParams().char_radius, 10);
    MOAIDraw::DrawLine(USVec2D(mCharacter->GetLoc()), mProjLocation);
}
