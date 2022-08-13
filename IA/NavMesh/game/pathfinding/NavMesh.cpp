#include "stdafx.h"
#include "NavMesh.h"
#include <tinyxml.h>

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
        int32_t polygonIndex = 0;
        int32_t edgeStart = 0;
        int32_t edgeEnd = 0;
        startElement->Attribute("polygon", &polygonIndex);
        startElement->Attribute("edgestart", &edgeStart);
        startElement->Attribute("edgeend", &edgeEnd);

        TiXmlElement* endElement = linkElement->FirstChildElement("end");
        int32_t neighbourIndex = 0;
        int32_t neighbourEdgeStart = 0;
        int32_t neighbourEdgeEnd = 0;
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
