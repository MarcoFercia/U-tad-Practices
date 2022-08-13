#pragma once
//#include "../lib/glm/glm.hpp"
#include <glm.hpp>

struct  Vertex
{
    Vertex(glm::vec3 _pos, glm::vec3 _color, glm::vec2 _textCoord, glm::vec3 _norm);
    Vertex(){}


    glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);
    glm::vec2 textCoord = glm::vec2(0.f, 0.f);
    glm::vec3 normal = glm::vec3(0.f, 0.f, 0.f);
};



struct IndexVex
{
    IndexVex(uint16_t _indexVertex);

    uint16_t indexVertex;
};