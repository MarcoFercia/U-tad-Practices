#pragma once

#include <vector>
#include <glm.hpp>

class Camera;
class Entity;
class Light;

class World 
{

public:
    World();
    ~World();

public:

protected:

private:

    std::vector<Entity*> Entities;
    std::vector<Camera*> Cameras;
    std::vector<Light*> Lights;

    glm::vec3 wolrdAmbient;

public:

    void addEntity(Entity* _entity);
    void removeEntity(const Entity* _entity);
    size_t getNumEntities() const;
    Entity* getEntity(size_t _index);
     glm::vec3 getAmbient();
    void setAmbient( glm::vec3 _ambient);

    void update(float _deltaTime);
    void draw();

protected:

private:



};

