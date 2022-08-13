
#include "Entity.h"

Entity::Entity()
{

}

const glm::vec3& Entity::getPosition() const
{
    return vPosition;
}

const glm::vec3& Entity::getRotation() const
{
    return vRotation;
}

const glm::vec3& Entity::getScale() const
{
    return vScale;
}

void Entity::setPosition(const glm::vec3& _pos)
{
    vPosition = _pos;
}

const void Entity::setRotation(const glm::vec3& _rot)
{
    
    vRotation = _rot;

}

void Entity::setScale(const glm::vec3& _scale)
{
    vScale = _scale;
}

void Entity::move(const glm::vec3& _vec)
{
    vPosition += _vec;
}

