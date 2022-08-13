#include "Buffer.h"
#include "State.h"




Buffer::Buffer(std::vector<Vertex> _vertex, std::vector<IndexVex> _index,  Shader* _shader/* = nullptr*/) :
    pShader(_shader),
    pos(glm::vec3(0.0f)),
    rot(0)
{
    glGenBuffers(1, &bufferVertex);
    glGenBuffers(1, &bufferVertexId);

    glBindBuffer(GL_ARRAY_BUFFER, bufferVertex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferVertexId);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertex.size(), _vertex.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * _index.size(), _index.data(), GL_STATIC_DRAW);

    indexsize = _index.size();
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &bufferVertex);
    glDeleteBuffers(1, &bufferVertexId);
}

void Buffer::Draw() const
{
     Shader* tempShader = pShader ? pShader : State::defaultShader;
   

    tempShader->setMatrix(0, State::projectionMatrix * State::viewMatrix * State::modelMatrix);

    glBindBuffer(GL_ARRAY_BUFFER, bufferVertex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferVertexId);

    tempShader->use();
    tempShader->setupAttribs();

    glDrawElements(GL_TRIANGLES, indexsize, GL_UNSIGNED_SHORT, nullptr);
}

void Buffer::setPosition(glm::vec3 _pos)
{
    pos = _pos;
}

void Buffer::setRotation(float _rot)
{
    rot = _rot;
}

glm::vec3 Buffer::getPosition()
{
    return pos;
}

float Buffer::getRotation()
{
    return rot;
}
