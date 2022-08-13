#pragma once
//#include "fwd.hpp"
//#include "GL/glew.h"
#include "VertexVec.h"
#include <vector>
#include "Shader.h"



class Buffer
{
public:

    Buffer(std::vector<Vertex> _vertex, std::vector<IndexVex> _index);

    ~Buffer();

    void Draw(const Shader& shader) const;

private:

    


    GLuint bufferVertex;
    GLuint bufferVertexId;


    int indexsize;
};