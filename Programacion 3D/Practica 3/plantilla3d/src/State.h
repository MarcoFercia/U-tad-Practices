#pragma once
#include "Shader.h"
#include "detail/type_mat.hpp"


class State
{

public:
    static Shader* defaultShader;
    static glm::mat4 projectionMatrix;
    static glm::mat4 viewMatrix;
    static glm::mat4 modelMatrix;

};

