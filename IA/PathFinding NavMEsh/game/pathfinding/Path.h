#pragma once

class Path
{
public:
    struct PointSegment
    {
        USVec2D SegmentPoint{};
        unsigned int SegmentIndex = 0;
    };

    void AddPoint(const USVec2D& _point);
    void Clear();
    bool Empty() const { return mPath.empty(); }

   
    PointSegment GetClosestPoint(const USVec2D _point) const;
    USVec2D GetPointAhead(const PointSegment& _point, float _distance) const;
    void DrawDebug();

private:
    std::vector<USVec2D> mPath;

};