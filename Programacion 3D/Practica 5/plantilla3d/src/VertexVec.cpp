#include "VertexVec.h"


Vertex::Vertex(glm::vec3 _pos, glm::vec3 _color, glm::vec2 _textCoord, glm::vec3 _norm)
{
    position = _pos;
    color = _color;
    textCoord = _textCoord;
    normal = _norm;

}

IndexVex::IndexVex(uint16_t _indexVertex)
{
    indexVertex = _indexVertex;
}
