#pragma once
#include "Shader.h"
#include "detail/type_mat.hpp"
#include <vector>

class Light;


class State
{

public:
    static Shader* defaultShader;
    static glm::mat4 projectionMatrix;
    static glm::mat4 viewMatrix;
    static glm::mat4 modelMatrix;
    static std::vector<Light*>lights;
    static glm::vec3 ambient;
};

