#include "stdafx.h"
#include "NavMesh.h"
#include <tinyxml.h>


// 
// bool Functions::IsPointInsidePolygon(const Polygon& _polygon, const USVec2D& _point)
// {
// 
// }
// 
// USVec2D Functions::GetCenterOfPolygon(const Polygon& _polygon)
// {
// 
// }


NavMesh::NavMesh()
{

}

NavMesh::~NavMesh()
{

}

NavMesh* NavMesh::Load(const char* _filename)
{
    TiXmlDocument doc(_filename);
    if (!doc.LoadFile())
    {
        printf("Couldn't read %s\n", _filename);
        return nullptr;
    }
    TiXmlHandle handleDoc(&doc);
    TiXmlElement* element = handleDoc.FirstChildElement().Element();
    if (!element)
    {
        printf("Invalid format\n");
        return nullptr;
    }

    // Create the navigation mesh
    NavMesh* navMesh = new NavMesh();

    // Get the root of polygons
    TiXmlHandle handleRoot(element);
    TiXmlHandle handlePolygons = handleRoot.FirstChildElement("polygons");

    // Read polygons
    TiXmlElement* polygonElement = handlePolygons.FirstChildElement("polygon").Element();
    for (polygonElement; polygonElement; polygonElement = polygonElement->NextSiblingElement())
    {
        Polygon* polygon = new Polygon();
        TiXmlElement* pointElement = polygonElement->FirstChildElement("point");
        for (pointElement; pointElement; pointElement = pointElement->NextSiblingElement())
        {
            float x = 0.f;
            float y = 0.f;
            pointElement->Attribute("x", &x);
            pointElement->Attribute("y", &y);
            polygon->vertex.push_back(USVec2D(x, y));
        }
        navMesh->polygons.push_back(polygon);
    }

    // Read links
    TiXmlHandle handleLink = handleRoot.FirstChildElement("links");
    TiXmlElement* linkElement = handleLink.FirstChildElement("link").Element();
    for (linkElement; linkElement; linkElement = linkElement->NextSiblingElement())
    {
        TiXmlElement* startElement = linkElement->FirstChildElement("start");
        int polygonIndex = 0;
        int edgeStart = 0;
        int edgeEnd = 0;
        startElement->Attribute("polygon", &polygonIndex);
        startElement->Attribute("edgestart", &edgeStart);
        startElement->Attribute("edgeend", &edgeEnd);

        TiXmlElement* endElement = linkElement->FirstChildElement("end");
        int neighbourIndex = 0;
        int neighbourEdgeStart = 0;
        int neighbourEdgeEnd = 0;
        endElement->Attribute("polygon", &neighbourIndex);
        endElement->Attribute("edgestart", &neighbourEdgeStart);
        endElement->Attribute("edgeend", &neighbourEdgeEnd);

        Polygon* firstPoly = navMesh->polygons.at(polygonIndex);
        Polygon* secondPoly = navMesh->polygons.at(neighbourIndex);

        Link firstLink;
        firstLink.neighbour = secondPoly;
        firstLink.edgeStart = edgeStart;
        firstLink.edgeEnd = edgeEnd;
        firstPoly->links.push_back(firstLink);

        Link secondLink;
        secondLink.neighbour = firstPoly;
        secondLink.edgeStart = neighbourEdgeStart;
        secondLink.edgeEnd = neighbourEdgeEnd;
        secondPoly->links.push_back(secondLink);
    }
    return navMesh;
}

void NavMesh::DrawDebug() const
{
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

    for (const Polygon* polygon : polygons)
    {
        gfxDevice.SetPenColor(0.1f, 0.1f, 0.4f, 0.5f);
        MOAIDraw::DrawPolygonFilled(polygon->vertex);
        gfxDevice.SetPenColor(0.7f, 0.1f, 0.2f, 0.5f);
        MOAIDraw::DrawPolygon(polygon->vertex);

        gfxDevice.SetPenColor(0.4f, 0.1f, 0.6f, 0.4f);
        for (const Link& link : polygon->links)
        {
            USVec2D edgeStart = polygon->vertex.at(link.edgeStart);
            USVec2D edgeEnd = polygon->vertex.at(link.edgeEnd);

            USVec2D edgeCenter = edgeEnd - edgeStart;
            edgeCenter *= 0.5f;
            edgeCenter += edgeStart;
            MOAIDraw::DrawEllipseFill(edgeCenter.mX, edgeCenter.mY, 5.f, 5.f, 10);
        }
    }
}

Polygon* NavMesh::GetPolygon(USVec2D& _Pos)
{
    for ( Polygon* polygon : polygons)
    {
        if (polygon->Inside(_Pos))
        {
            return polygon;
        }
    }
    return nullptr;
}

bool NavMesh::StartPolygon( USVec2D& _Pos)
{
    startPolygon = GetPolygon(_Pos);
    return startPolygon != nullptr;
}

bool NavMesh::EndPolygon( USVec2D& _Pos)
{
    endPolygon = GetPolygon(_Pos);
    return endPolygon != nullptr;
}



USVec2D Polygon::Center() const
{
    USVec2D pointcenter(0.f, 0.f);

    float zone = 0.f;

    for (unsigned int i = 0; i < vertex.size(); ++i)
    {

        USVec2D vertex1(vertex.at(i).mX, vertex.at(i).mY);
        USVec2D vertex2(vertex.at((i + 1) % vertex.size()).mX, vertex.at((i + 1) % vertex.size()).mY);
        
        float temp = (vertex1.mX * vertex2.mY) - (vertex2.mX * vertex1.mY);

        zone += temp;

        pointcenter.mX += (vertex1.mX + vertex2.mX) * temp;
        pointcenter.mY += (vertex1.mY + vertex2.mY) * temp;

    }
    return pointcenter;
}

bool Polygon::Inside(const USVec2D& _point) const
{
    bool inside = false;
    for (unsigned int i = 0, j = vertex.size() - 1; i < vertex.size(); j = i++)
    {
        USVec2D vertexi = vertex.at(i);
        USVec2D vertexj = vertex.at(j);
        if ((vertexi.mY > _point.mY != vertexj.mY > _point.mY) && (_point.mX < (vertexj.mX - vertexi.mX) * (_point.mY - vertexi.mY) / (vertexj.mY - vertexi.mY) + vertexi.mX))
        {
            inside = !inside;
        }
    }
    return inside;
}

USVec2D Polygon::GetMidPoint(const Link& _link) const
{
     USVec2D start = vertex.at(_link.edgeStart);
     USVec2D end = vertex.at(_link.edgeEnd);
    return start + (end - start) * 0.5f;
}
