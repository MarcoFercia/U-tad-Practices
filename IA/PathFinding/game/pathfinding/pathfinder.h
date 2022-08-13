#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#include <moaicore/MOAIEntity2D.h>

struct Node;
class Grid;

class Pathfinder: public virtual MOAIEntity2D
{
public:
	Pathfinder();
	~Pathfinder();

	virtual void DrawDebug();

	void SetStartPosition(float x, float y);
	void SetEndPosition(float x, float y);
	const USVec2D& GetStartPosition() const;
	const USVec2D& GetEndPosition() const;

    bool PathfindStep();
private:
	void UpdatePath();
	float CalculateValue(const USVec2D& _point);
	void FillPath(Node* _end);
	Node* GetNodeInVector(std::vector<Node*>& _vector, const USVec2D& _nodePosition) const;
	void DrawNodes(const std::vector<Node*>& _vector, float _radius, const USVec4D& _color) const;



	USVec2D m_StartPosition;
	USVec2D m_EndPosition;

    USVec2D m_startGridPosition;
    USVec2D m_endGridPosition;

    Grid* mGrid;
    Node* m_currentNode;
    std::vector<Node*> mOpenNodes;
    std::vector<Node*> mCloseNodes;
    std::vector<Node*> mPath;


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