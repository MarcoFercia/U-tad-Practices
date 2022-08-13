#include <stdafx.h>
#include "Path.h"
#include "tinyxml.h"

void Path::Load(const char* _filename)
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
    TiXmlHandle hParams = hRoot.FirstChildElement("points");

    TiXmlElement* paramElem = hParams.FirstChild().Element();
    for (paramElem; paramElem; paramElem = paramElem->NextSiblingElement())
    {
        const char* paramName = paramElem->Value();
        if (!strcmp(paramName, "point"))
        {
            USVec2D point;
            paramElem->Attribute("x", &point.mX);
            paramElem->Attribute("y", &point.mY);
            mPath.push_back(point);
        }
    }
}

Path::PointSegment Path::GetClosestPoint(const USVec2D _point) const
{
    PointSegment closePoint;
    float minSquareDistance = -1;
    for (unsigned int index = 0; index < mPath.size() - 1; ++index)
    {
        USVec2D PathPoint;
        USVec2D origin = mPath.at(index);
        USVec2D end = mPath.at(index + 1);
        float coso = (end.mX - origin.mX) * (end.mX - origin.mX) + (end.mY - origin.mY) * (end.mY - origin.mY);

        if (coso!= 0.f)
        {
            float x = ((_point.mX - origin.mX) * (end.mX - origin.mX) + (_point.mY - origin.mY) * (end.mY - origin.mY)) / coso;

            if (x < 0.f)
            {
                PathPoint = origin;
            }
            else if (x > 1.f)
            {
                PathPoint = end;
            }
            else
            {
                PathPoint = { origin.mX + x * (end.mX - origin.mX), origin.mY + x * (end.mY - origin.mY) };
            }
            float squareDistance = PathPoint.DistSqrd(_point);

            if (minSquareDistance < 0.f || squareDistance < minSquareDistance)
            {
                minSquareDistance = squareDistance;
                closePoint.SegmentPoint = PathPoint;
                closePoint.SegmentIndex = index;
            }
        }
    }
    return closePoint;
}

USVec2D Path::GetPointAhead(const PointSegment& _point, float _distance) const
{
    std::vector<USVec2D>::const_iterator it = mPath.begin() + _point.SegmentIndex;
    USVec2D segmentDirection = *(it + 1) - *it;
    segmentDirection.NormSafe();
    USVec2D nextPoint = _point.SegmentPoint + segmentDirection * _distance;

    if ((nextPoint - *it).LengthSquared() > (*(it + 1) - *it).LengthSquared() && it + 2 != mPath.end())
    {
        float LeftDisance = _distance - (*(it + 1) - _point.SegmentPoint).Length();
        segmentDirection = *(it + 2) - *(it + 1);
        segmentDirection.NormSafe();
        nextPoint = *(it + 1) + segmentDirection * LeftDisance;
    }
    else if (it + 2 == mPath.end())
    {
        nextPoint = *(it + 1);
    }
    return nextPoint;
}

void Path::DrawDebug()
{
    for (size_t index = 0; index < mPath.size(); ++index)
    {
        USVec2D Point = mPath.at(index);
        MOAIDraw::DrawEllipseFill(Point.mX, Point.mY, 2.f, 2.f, 10);
        if (index < mPath.size() - 1)
        {
            MOAIDraw::DrawLine(Point, mPath.at(index + 1));
        }
    }
}
