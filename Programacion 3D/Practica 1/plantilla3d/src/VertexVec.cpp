#include "VertexVec.h"


Vertex::Vertex(glm::vec3 _pos, glm::vec3 _color)
{
    position = _pos;
    color = _color;
}

IndexVex::IndexVex(uint16_t _indexVertex)
{
    indexVertex = _indexVertex;
}
