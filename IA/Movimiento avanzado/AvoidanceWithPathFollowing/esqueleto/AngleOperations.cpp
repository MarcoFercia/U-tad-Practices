#include <stdafx.h>
#include "AngleOperations.h"


#define PI 3.14159265358979323846


void AnlgesOperations::NormalizeRadAngle(float& angleInRadians)
{
    if (angleInRadians < -(float(PI)) || angleInRadians > float(PI))
    {
        const int x = int(fmodf(angleInRadians, PI));
        angleInRadians += 2 * float(PI) * -1.f * float(x);
    }
}

void AnlgesOperations::NormalizeDegAngle(float& angleInDegrees)
{
    while (angleInDegrees > 180.f)
    {
        angleInDegrees -= 360.f;
    }
    while (angleInDegrees < -180.f)
    {
        angleInDegrees += 360.f;
    }
}

float AnlgesOperations::ToRadians(float angleInDegrees)
{
    float x = angleInDegrees * float(PI) / 180.f;
    return x;
}

float AnlgesOperations::ToDegrees(float angleInRadians)
{
    float x = angleInRadians * 180.f / float(PI);
    return x;
}
