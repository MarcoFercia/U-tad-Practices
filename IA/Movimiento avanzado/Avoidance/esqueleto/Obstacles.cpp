#include <stdafx.h>
#include "Obstacles.h"
#include "tinyxml.h"

Obstacle::Obstacle(const USVec2D& _position, float _radius) : mPosition(_position), mRadius(_radius), mIsColliding(false)
{

}

void Obstacle::LoadFromFile(std::vector<Obstacle*>& obstacles_, const char* _filename)
{
    TiXmlDocument doc(_filename);
    if (!doc.LoadFile())
    {
        fprintf(stderr, "Couldn't read params from %s", _filename);
        return;
    }

    TiXmlHandle hDoc(&doc);

    TiXmlElement* pElem;
    pElem = hDoc.FirstChildElement().Element();
    if (!pElem)
    {
        fprintf(stderr, "Invalid format for %s", _filename);
        return;
    }

    TiXmlHandle hRoot(pElem);
    TiXmlHandle hParams = hRoot.FirstChildElement("obstacles");

    TiXmlElement* paramElem = hParams.FirstChild().Element();
    for (paramElem; paramElem; paramElem = paramElem->NextSiblingElement())
    {
        const char* paramName = paramElem->Value();
        if (!strcmp(paramName, "obstacle"))
        {
            USVec2D pos;
            paramElem->Attribute("x", &pos.mX);
            paramElem->Attribute("y", &pos.mY);
            float radius;
            paramElem->Attribute("r", &radius);
            obstacles_.push_back(new Obstacle(pos, radius));
        }
    }
}

const USVec2D& Obstacle::GetPosition() const
{
    return mPosition;
}

float Obstacle::GetRadius() const
{
    return mRadius;
}

void Obstacle::DrawDebug() const
{
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

    if (IsColliding())
    {
        gfxDevice.SetPenColor(1.f, 0.1f, 0.1f, 1.f);
    }
    else
    {
        gfxDevice.SetPenColor(1.f, 1.f, 1.f, 1.f);
    }
    MOAIDraw::DrawEllipseOutline(mPosition.mX, mPosition.mY, mRadius, mRadius, 10);
}
