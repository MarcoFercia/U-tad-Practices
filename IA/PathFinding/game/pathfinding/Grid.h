#pragma once



struct Node
{
    Node* Parent;
    USVec2D Pos;
    float HCost;
    float GCost;
    float GetCost() const { return HCost + GCost; }

    Node(Node* _parent, const USVec2D& _posGrid, float _HCost, float _GCost) : Parent(_parent), Pos(_posGrid), HCost(_HCost), GCost(_GCost) {}

    Node(const Node*& _other) : Parent(_other->Parent), Pos(_other->Pos), HCost(_other->HCost), GCost(_other->GCost) {}

};



class Grid
{
public:
    static Grid* Load(const char* _mapFilename, const char* _codeFilename);

    Grid();

    float GetCost(uint32_t _index) const;
    float GetCost(uint32_t _row, uint32_t _col) const;
    float GetCost(const USVec2D& _gridLocation) const;
    USVec2D GetSize() const;
    USVec2D GetRectSize() const;
    bool IsValidPos(const USVec2D _pos) const;
    USVec2D GridToWorldLocation(const USVec2D& _gridLocation) const;
    USVec2D WorldToGridLocation(const USVec2D& _worldLocation) const;
    void DrawDebug() const;
    void DrawRectangle(const USVec2D& _gridPosition, const USVec4D& _color) const;

private:
    std::vector<float> mMap;
    USVec2D mSize;

};

