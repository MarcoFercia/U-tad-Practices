#include "VertexVec.h"


Vertex::Vertex(glm::vec3 _pos, glm::vec3 _color, glm::vec2 _textCoord)
{
    position = _pos;
    color = _color;
    textCoord = _textCoord;
}

IndexVex::IndexVex(uint16_t _indexVertex)
{
    indexVertex = _indexVertex;
}
