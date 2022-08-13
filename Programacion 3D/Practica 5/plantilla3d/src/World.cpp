#include "World.h"
#include "Entity.h"
#include "Camera.h"
#include "light.h"
#include "State.h"


World::World()
{

}

World::~World()
{

}


void World::addEntity(Entity* _entity)
{
    Entities.push_back(_entity);
    Camera* tempCamera = dynamic_cast<Camera*>(_entity);
    if (tempCamera)
    {
        Cameras.push_back(tempCamera);
    }

    Light* tempLight = dynamic_cast<Light*>(_entity);
    if (tempLight)
    {
        Lights.push_back(tempLight);
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


    std::vector<Light*>::iterator iterLight;

    for (iterLight = Lights.begin(); iterLight != Lights.end(); ++iterLight)
    {
        if (*iterLight == _entity)
        {
            Lights.erase(iterLight);
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

 glm::vec3 World::getAmbient() 
{
     return wolrdAmbient;
}

void World::setAmbient( glm::vec3 _ambient)
{
    wolrdAmbient = _ambient;
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

    State::lights = Lights;
    State::ambient = wolrdAmbient;



    for (Camera* it : Cameras)
    {
        it->prepare();
    }

    for (Entity* it : Entities)
    {
        it->draw();
    }
}
