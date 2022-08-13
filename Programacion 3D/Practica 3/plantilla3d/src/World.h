#pragma once

#include <vector>


class Camera;
class Entity;

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

public:

    void addEntity(Entity* _entity);
    void removeEntity(const Entity* _entity);
    size_t getNumEntities() const;
    Entity* getEntity(size_t _index);


    void update(float _deltaTime);
    void draw();

protected:

private:



};

