#include "Buffer.h"




Buffer::Buffer(std::vector<Vertex> _vertex, std::vector<IndexVex> _index)
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

void Buffer::Draw(const Shader& shader) const
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferVertex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferVertexId);

    shader.use();
    shader.setupAttribs();

    glDrawElements(GL_TRIANGLES, indexsize, GL_UNSIGNED_SHORT, nullptr);
}
