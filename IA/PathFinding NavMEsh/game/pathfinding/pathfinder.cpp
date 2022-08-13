#include <stdafx.h>
#include "pathfinder.h"
#include <algorithm>
#include "NavMesh.h"
#include "Path.h"


Pathfinder::Pathfinder() : MOAIEntity2D()
{
	RTTI_BEGIN
		RTTI_EXTEND(MOAIEntity2D)
		RTTI_END

	navMesh = NavMesh::Load("filenavmesh1.xml");
    path = new Path();

    if (instance==nullptr)
    {
        instance = this;
    }

}

Pathfinder::~Pathfinder()
{
    Clear();
}


void Pathfinder::SetStartPosition(float x, float y)
{
    m_StartPosition = USVec2D(x, y);
    navMesh->StartPolygon(m_StartPosition);
    UpdatePath();
}

void Pathfinder::SetEndPosition(float x, float y)
{
	m_EndPosition = USVec2D(x, y);
    navMesh->EndPolygon(m_EndPosition);
    UpdatePath();
}


void Pathfinder::UpdatePath()
{
    Clear();

    Polygon* startPolygon = navMesh->GetPolygon(m_StartPosition);
    if (startPolygon)
    {
        openNodes.push_back(new Node(nullptr, m_StartPosition, startPolygon, 0, CalculateValue(m_StartPosition)));
    }
}

float Pathfinder::CalculateValue(const USVec2D& _point)
{
    return _point.DistSqrd(m_EndPosition);
}

void Pathfinder::Clear()
{
    for (Node*& it : openNodes)
    {
        if (it)
        {
            delete it;
            it = nullptr;
        }
    }
    for (Node*& it : closeNodes)
    {
        if (it)
        {
            delete it;
            it = nullptr;
        }
    }
    path->Clear();
    openNodes.clear();
    closeNodes.clear();
}

void Pathfinder::FillPath(const Node* _node)
{
    const Node* it = _node;
    path->AddPoint(m_EndPosition);
    while (it)
    {
        path->AddPoint(it->Position);
        it = it->Parent;
    }
}


Node* Pathfinder::GetNodeInVector(std::vector<Node*>& _vector, const Polygon* _polygon)
{

    for (Node* it : _vector)
    {
        if (it->polygon == _polygon)
        {
            return it;
        }
    }
    return nullptr;

}

void Pathfinder::DrawDebug()
{
	navMesh->DrawDebug();

    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

    // Draw start and end position
    gfxDevice.SetPenColor(0.2f, 0.9f, 0.5f, 1.f);
    USVec2D PointCross = m_StartPosition + USVec2D(-15.f, -15.f);
    USVec2D vectordirection = m_StartPosition - PointCross;
    MOAIDraw::DrawLine(PointCross, PointCross + (vectordirection * 2.f));

     PointCross = m_StartPosition + USVec2D(15.f, -15.f);
     vectordirection = m_StartPosition - PointCross;
    MOAIDraw::DrawLine(PointCross, PointCross + (vectordirection * 2.f));




    gfxDevice.SetPenColor(0.9f, 0.2f, 0.5f, 1.f);
    PointCross = m_EndPosition + USVec2D(-15.f, -15.f);
    vectordirection = m_EndPosition - PointCross;
    MOAIDraw::DrawLine(PointCross, PointCross + (vectordirection * 2.f));

    PointCross = m_EndPosition + USVec2D(15.f, -15.f);
    vectordirection = m_EndPosition - PointCross;
    MOAIDraw::DrawLine(PointCross, PointCross + (vectordirection * 2.f));





  



    // Draw open and close nodes
    gfxDevice.SetPenColor(0.8f, 0.3f, 0.3f, 1.f);
    for (Node* it : openNodes)
    {
        if (it)
        {
            MOAIDraw::DrawEllipseFill(it->Position.mX, it->Position.mY, 5.f, 5.f, 10);
        }
    }
    gfxDevice.SetPenColor(0.3f, 0.3f, 0.3f, 1.f);
    for (Node* it : closeNodes)
    {
        if (it)
        {
            MOAIDraw::DrawEllipseFill(it->Position.mX, it->Position.mY, 5.f, 5.f, 10);
        }
    }

    // Draw path
    path->DrawDebug();


}

bool Pathfinder::PathfindStep()
{
    
    if (path->Empty() && !openNodes.empty())
    {
        // Sort open list and get the first value
        std::sort(openNodes.begin(), openNodes.end(),
            [](const Node* _first, const Node* _second) -> bool
            {
                return _first->GetCost() < _second->GetCost();
            }
        );

        Node* currentNode = openNodes.at(0);
        openNodes.erase(openNodes.begin());
        closeNodes.push_back(currentNode);

        // Check if the current node is our aim
        if (currentNode->polygon == navMesh->GetEndPolygon())
        {
            FillPath(currentNode);
            return true;
        }

        for (const Link& link : currentNode->polygon->links)
        {
            Polygon* nextPolygon = link.neighbour;
            Node* repeatedNode = GetNodeInVector(closeNodes, nextPolygon);
            if (!repeatedNode)
            {
                repeatedNode = GetNodeInVector(openNodes, nextPolygon);
                const float costG = currentNode->CostG + 1.f;
                if (repeatedNode)
                {
                    if (costG < repeatedNode->CostG)
                    {
                        repeatedNode->CostG = costG;
                        repeatedNode->Parent = currentNode;
                    }
                }
                else
                {
                    const USVec2D pos = currentNode->polygon->GetMidPoint(link);
                    Node* node = new Node(currentNode, pos, nextPolygon, costG, CalculateValue(pos));
                    openNodes.push_back(node);
                }
            }
        }
    }
    return false;
}















//lua configuration ----------------------------------------------------------------//
void Pathfinder::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity::RegisterLuaFuncs(state);

	luaL_Reg regTable [] = {
		{ "setStartPosition",		_setStartPosition},
		{ "setEndPosition",			_setEndPosition},
        { "pathfindStep",           _pathfindStep},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Pathfinder::_setStartPosition(lua_State* L)
{
	MOAI_LUA_SETUP(Pathfinder, "U")

	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetStartPosition(pX, pY);
	return 0;
}

int Pathfinder::_setEndPosition(lua_State* L)
{
	MOAI_LUA_SETUP(Pathfinder, "U")

	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetEndPosition(pX, pY);
	return 0;
}

int Pathfinder::_pathfindStep(lua_State* L)
{
    MOAI_LUA_SETUP(Pathfinder, "U")

    self->PathfindStep();
    return 0;
}