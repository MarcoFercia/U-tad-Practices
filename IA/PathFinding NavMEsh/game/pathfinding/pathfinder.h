#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#include <moaicore/MOAIEntity2D.h>
#include "NavMesh.h"
#include "Path.h"


class Path;

struct Node
{
    Node* Parent;
    USVec2D Position;
    Polygon* polygon;
    float CostH;
    float CostG;
    float GetCost() const { return CostH + CostG; }

    Node(Node* _parent, const USVec2D& _position, Polygon* _polygon, float _costG, float _costH)
        : Parent(_parent), Position(_position), polygon(_polygon), CostG(_costG), CostH(_costH) {}
};





class Pathfinder: public virtual MOAIEntity2D
{
public:
	Pathfinder();
	~Pathfinder();

	virtual void DrawDebug();

	void SetStartPosition(float x, float y);
    void SetEndPosition(float x, float y);
	const USVec2D& GetStartPosition() const { return m_StartPosition;}
	const USVec2D& GetEndPosition() const { return m_EndPosition;}

    bool PathfindStep();

    const Path* GetPath() const { return path; }
    bool IsPathCompleted() const { return !path->Empty(); }

private:
	void UpdatePath();
    float CalculateValue(const USVec2D& _point) ;
    void Clear();
    void FillPath(const Node* _node);
    Node* GetNodeInVector(std::vector<Node*>& _vector, const Polygon* _polygon);



private:
	USVec2D m_StartPosition;
	USVec2D m_EndPosition;

	NavMesh* navMesh;
    Path* path;

    std::vector<Node*> openNodes;
    std::vector<Node*> closeNodes;

    Pathfinder* instance;


	// Lua configuration
public:
	DECL_LUA_FACTORY(Pathfinder)
public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
	static int _setStartPosition(lua_State* L);
	static int _setEndPosition(lua_State* L);
    static int _pathfindStep(lua_State* L);
};


#endif