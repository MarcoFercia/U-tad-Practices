#pragma once
#include <vector>
#include "uslscore/USVec2D.h"

class Obstacle
{

public:
    static void LoadFromFile(std::vector<Obstacle*>& obstacles_, const char* _filename);

    Obstacle(const USVec2D& _position, float _radius);

    const USVec2D& GetPosition() const;
    float GetRadius() const;

    void DrawDebug() const;

    bool IsColliding() const { return mIsColliding; }
    void SetIsColliding(bool _isColliding) { mIsColliding = _isColliding; }

private:
    USVec2D mPosition;
    float mRadius = 0.f;
    bool mIsColliding = false;

};