#pragma once


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
};




class NavMesh
{
public:
    NavMesh();
    ~NavMesh();

    static NavMesh* Load(const char* _filename);

    void DrawDebug() const;

private:

    std::vector<Polygon*> polygons;

};

