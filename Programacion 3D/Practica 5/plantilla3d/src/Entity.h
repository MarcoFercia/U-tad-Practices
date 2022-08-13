#pragma once
#include "gtx/transform.hpp"



class Entity
{
public:

    Entity();
    virtual ~Entity() {}

public:
protected:
    glm::vec3 vPosition;
    glm::vec3 vRotation;
    glm::vec3 vScale;

private:



public:

    const glm::vec3& getPosition() const;
    const glm::vec3& getRotation() const; // puede ser quat
    const glm::vec3& getScale() const;
    
    void setPosition(const glm::vec3& _pos);
    const void setRotation(const glm::vec3& _rot); // puede ser quat
    void setScale(const glm::vec3& _scale);
    
    
    void move(const glm::vec3& _vec); // ver en las diapositivas
    
    
    
    virtual void update(float _deltaTime) {}
    virtual void draw() {}

protected:
private:


   

};

