#include <stdafx.h>

#include "pathfinder.h"
#include "Grid.h"
#include <algorithm>

Pathfinder::Pathfinder() : MOAIEntity2D()
{
    RTTI_BEGIN
        RTTI_EXTEND(MOAIEntity2D)
        RTTI_END

        mGrid = Grid::Load("map.txt", "MapCode.txt");
    m_currentNode = nullptr;
}

Pathfinder::~Pathfinder()
{
    mPath.clear();
    mOpenNodes.clear();
    mCloseNodes.clear();
}

void Pathfinder::UpdatePath()
{
    mPath.clear();
    mOpenNodes.clear();
    mCloseNodes.clear();

    mOpenNodes.push_back(new Node(nullptr, m_startGridPosition, 0, CalculateValue(m_startGridPosition)));
}

float Pathfinder::CalculateValue(const USVec2D& _point)
{
    return fabsf(_point.mX - m_endGridPosition.mX) + fabsf(_point.mY - m_endGridPosition.mY);
}

void Pathfinder::FillPath(Node* _end)
{
    Node* node = _end;

    while (node)
    {
        mPath.insert(mPath.begin(), node);
        node = node->Parent;
    }
}

Node* Pathfinder::GetNodeInVector(std::vector<Node*>& _vector, const USVec2D& _nodePosition) const
{
    for (Node* it : _vector)
    {
        if (it->Pos.Equals(_nodePosition))
        {
            return it;
        }
    }
    return nullptr;
}

void Pathfinder::DrawNodes(const std::vector<Node*>& _vector, float _radius, const USVec4D& _color) const
{
    for (Node* it : _vector)
    {
        USVec2D center = mGrid->GridToWorldLocation(it->Pos);
        center += mGrid->GetRectSize() * 0.5f;
        MOAIGfxDevice::Get().SetPenColor(_color.mX, _color.mY, _color.mZ, _color.mW);
        MOAIDraw::DrawEllipseFill(center.mX, center.mY, _radius, _radius, 10);
    }
}

void Pathfinder::DrawDebug()
{
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

    // Draw grid.
    mGrid->DrawDebug();

    // Draw start and end position.
    gfxDevice.SetPenColor(1.f, 1.f, 0.f, 1.f);
    USVec2D startCenter = mGrid->GridToWorldLocation(m_startGridPosition);
    startCenter += mGrid->GetRectSize() * 0.5f;
   
    USVec2D PointCross = startCenter + USVec2D(-7.f, -7.f);
    USVec2D vectordirection = startCenter - PointCross;
    MOAIDraw::DrawLine(PointCross, PointCross + (vectordirection * 2.f));

    PointCross = startCenter + USVec2D(7.f, -7.f);
    vectordirection = startCenter - PointCross;
    MOAIDraw::DrawLine(PointCross, PointCross + (vectordirection * 2.f));


    gfxDevice.SetPenColor(0.8f, 0.17f, 0.57f, 1.f);
    USVec2D endCenter = mGrid->GridToWorldLocation(m_endGridPosition);
    endCenter += mGrid->GetRectSize() * 0.5f;
   
    PointCross = endCenter + USVec2D(-15.f, -15.f);
    vectordirection = endCenter - PointCross;
    MOAIDraw::DrawLine(PointCross, PointCross + (vectordirection * 2.f));

    PointCross = endCenter + USVec2D(15.f, -15.f);
    vectordirection = endCenter - PointCross;
    MOAIDraw::DrawLine(PointCross, PointCross + (vectordirection * 2.f));




    DrawNodes(mCloseNodes, 5.f, USVec4D(0.3f, 0.1f, 0.1f, 1.f));
    DrawNodes(mOpenNodes, 5.f, USVec4D(0.7f, 0.1f, 0.1f, 1.f));
    DrawNodes(mPath, 5.f, USVec4D(0.f, 1.f, 0.f, 1.f));
}

void Pathfinder::SetStartPosition(float x, float y)
{
    m_StartPosition = USVec2D(x, y);
    m_startGridPosition = mGrid->WorldToGridLocation(m_StartPosition);
    UpdatePath();
}

void Pathfinder::SetEndPosition(float x, float y)
{
    m_EndPosition = USVec2D(x, y);
    m_endGridPosition = mGrid->WorldToGridLocation(m_EndPosition);
    UpdatePath();
}

const USVec2D& Pathfinder::GetStartPosition() const
{
    return m_StartPosition;
}

const USVec2D& Pathfinder::GetEndPosition() const
{
    return m_EndPosition;
}

bool Pathfinder::PathfindStep()
{

    if (mPath.empty())
    {
        std::sort(mOpenNodes.begin(), mOpenNodes.end(),
            [](const Node* _first, const Node* _second) -> bool
            {
                return _first->GetCost() < _second->GetCost();
            }
        );


        m_currentNode = mOpenNodes.at(0);
        mOpenNodes.erase(mOpenNodes.begin());
        mCloseNodes.push_back(m_currentNode);

        if (m_currentNode->Pos.Equals(m_endGridPosition))
        {
            FillPath(m_currentNode);
            return true;
        }

        static const std::vector<USVec2D> deltaPositionOptions = {
            {-1.f, 0.f}, {0.f, 1.f},
            {1.f, 0.f},  {0.f, -1.f}
        };


        for (const USVec2D& deltaPosition : deltaPositionOptions)
        {
            const USVec2D nextPosition = m_currentNode->Pos + deltaPosition;
            // Is next position valid?
            if (mGrid->IsValidPos(nextPosition) && mGrid->GetCost(nextPosition) >= 0.f)
            {
                Node* repeatedNode = GetNodeInVector(mCloseNodes, nextPosition);
                // Check if the position represents some node which already exists in any vector
                if (repeatedNode == nullptr)
                {
                    repeatedNode = GetNodeInVector(mOpenNodes, nextPosition);
                    const float costG = m_currentNode->GCost + mGrid->GetCost(nextPosition);
                    const float costH = CalculateValue(nextPosition);
                    if (repeatedNode == nullptr)
                    {
                        Node* newNode = new Node(m_currentNode, nextPosition, costG, costH);
                        mOpenNodes.push_back(newNode);
                    }
                    else
                    {
                        if (costG < repeatedNode->GCost)
                        {
                            repeatedNode->GCost = costG;
                            repeatedNode->Parent = m_currentNode;
                        }
                    }
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

    luaL_Reg regTable[] = {
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