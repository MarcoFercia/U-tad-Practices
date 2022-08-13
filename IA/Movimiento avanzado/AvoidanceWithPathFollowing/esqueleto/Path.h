#pragma once
#include <vector>
#include "uslscore/USVec2D.h"


class Path
{
public:
    struct PointSegment
    {
        USVec2D SegmentPoint{};
        unsigned int SegmentIndex = 0;
    };


    void Load(const char* _filename);
    PointSegment GetClosestPoint(const USVec2D _point) const;
    USVec2D GetPointAhead(const PointSegment& _point, float _distance) const;
    void DrawDebug();

private:
    std::vector<USVec2D> mPath;

};