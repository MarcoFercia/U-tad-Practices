#pragma once
//#include "fwd.hpp"
//#include "GL/glew.h"
#include "VertexVec.h"
#include <vector>
#include "Shader.h"



class Buffer
{
public:

    Buffer(std::vector<Vertex> _vertex, std::vector<IndexVex> _index, Shader* _shader = nullptr);

    ~Buffer();

    void Draw() const;

    void setPosition(glm::vec3 _pos);
    void setRotation(float _rot);

    glm::vec3 getPosition();
    float getRotation();

private:

    
    Shader* pShader = nullptr;

    GLuint bufferVertex;
    GLuint bufferVertexId;


    int indexsize;

    float rot;
    glm::vec3 pos;
};