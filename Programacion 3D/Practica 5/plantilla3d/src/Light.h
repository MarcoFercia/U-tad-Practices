#pragma once
#include "Entity.h"
#include <glm.hpp>

class Shader;

enum class lightType
{
    Directional = 0,
    Point = 1
   
  
};


class Light : public Entity
{
public:

    Light();
    ~Light();
public:

protected:

private:

    glm::vec4 color;
    lightType myType;
    float linearAttenuation = 0.f;

public:
    lightType getType();
    void setType(lightType _type);

    const glm::vec3& getColor() const;
    void setColor(const glm::vec3 _color);

    float getLinearAttenuation() const;
    void setLinearAtteniation(float _attenuation);

    void prepare(int _index, Shader* _shader) const;

protected:

private:




};

