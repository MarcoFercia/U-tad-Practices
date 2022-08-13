#include "World.h"
#include "Entity.h"
#include "Camera.h"


World::World()
{

}

World::~World()
{

}


void World::addEntity(Entity* _entity)
{
    Entities.push_back(_entity);
    Camera* tempEntity = dynamic_cast<Camera*>(_entity);
    if (tempEntity)
    {
        Cameras.push_back(tempEntity);
    }
}

void World::removeEntity(const Entity* _entity)
{
    std::vector<Entity*>::iterator it;

    for (it = Entities.begin(); it != Entities.end(); ++it)
    {
        if (*it == _entity)
        {           
            Entities.erase(it);
            break;
        }
    }

    std::vector<Camera*>::iterator iter;

    for (iter = Cameras.begin(); iter != Cameras.end(); ++iter)
    {
        if (*iter == _entity)
        {
            Cameras.erase(iter);
            break;
        }
    }

}

size_t World::getNumEntities() const
{
    return Entities.size();
}

Entity* World::getEntity(size_t _index)
{
    if (_index < Entities.size())
    {
        return Entities[_index];
    }
    return nullptr;
}

void World::update(float _deltaTime)
{
    for (Entity* it : Entities)
    {
        it->update(_deltaTime);
    }
}

void World::draw()
{
    for (Camera* it : Cameras)
    {
        it->prepare();
    }

    for (Entity* it : Entities)
    {
        it->draw();
    }
}
