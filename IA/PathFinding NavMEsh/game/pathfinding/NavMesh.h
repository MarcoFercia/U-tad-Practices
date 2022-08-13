#pragma once

// namespace Functions
// {
//     bool IsPointInsidePolygon(const struct Polygon& _polygon, const USVec2D& _point);
//     USVec2D GetCenterOfPolygon(const struct Polygon& _polygon);
// }


struct Link
{
    struct Polygon* neighbour;
    int32_t edgeStart;
    int32_t edgeEnd;
};

struct Polygon
{
    std::vector<USVec2D> vertex;
    std::vector<Link> links;

    USVec2D Center() const;
    bool Inside(const USVec2D& _point) const;
    USVec2D GetMidPoint(const Link& _link) const;
};




class NavMesh
{
public:
    NavMesh();
    ~NavMesh();

    static NavMesh* Load(const char* _filename);
    void DrawDebug() const;

    Polygon* GetPolygon(USVec2D& _Pos);

    bool StartPolygon( USVec2D& _Pos);
    bool EndPolygon( USVec2D& _Pos);

     Polygon* GetStartPolygon()  { return startPolygon; }
     Polygon* GetEndPolygon()  { return endPolygon; }


private:

    std::vector<Polygon*> polygons;
    Polygon* startPolygon;
    Polygon* endPolygon;
};

