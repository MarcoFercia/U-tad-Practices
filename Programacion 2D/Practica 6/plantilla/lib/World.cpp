#include "World.h"
#include "sreensize.h"



World::World(float _clearRed, float _clearGreen, float _clearBlue,
    const ltex_t* _back0, const ltex_t* _back1,
    const ltex_t* _back2, const ltex_t* _back3) : clearRed(_clearRed), clearBlue(_clearBlue), clearGreen(_clearGreen)
{
    backimages[0].tex = _back0;
    backimages[1].tex = _back1;
    backimages[2].tex = _back2;
    backimages[3].tex = _back3;

}


World::~World()
{
    while (vSprites.size())
    {
        delete vSprites.back();
        vSprites.pop_back();
    }


}


float World::getClearRed() const
{
    return clearRed;
}

float World::getClearGreen() const
{
    return clearGreen;
}

float World::getClearBlue() const
{
    return clearBlue;
}

const ltex_t* World::getBackground(size_t _layer) const
{

    if (_layer >= 0 && _layer < 4)
    {
        return backimages[_layer].tex;
    }
    else
    {
        return nullptr;
    }
}

float World::getScrollRatio(size_t _layer) const
{


    if (_layer >= 0 && _layer < 4)
    {
        return backimages[_layer].scrollRatio;
    }
    else
    {
        return 0.f;
    }

}

void World::setScrollRatio(size_t _layer, float _ratio)
{
    if (_layer >= 0 && _layer < 4)
    {
        backimages[_layer].scrollRatio = _ratio;
    }
}

const vec2& World::getScrollSpeed(size_t _layer) const
{
    if (_layer >= 0 && _layer < 4)
    {
        return backimages[_layer].scrollSpeed;
    }

    return vec2(0.f, 0.f);
}

void World::setScrollSpeed(size_t _layer, const vec2& _speed)
{

    if (_layer >= 0 && _layer < 4)
    {
        backimages[_layer].scrollSpeed=_speed;
    }

}

const vec2& World::getCameraPosition() const
{
    return cameraPosition;
}

void World::setCameraPosition(const vec2& _pos)
{
    cameraPosition = _pos;
   
}

void World::addSprite(Sprite& _sprite)
{
    vSprites.push_back(&_sprite);
}

void World::removeSprite(Sprite& _sprite)
{

    vSprites.remove(&_sprite);
    
}

void World::update(float _deltaTime)
{
    // lgfx_setorigin(cameraPosition.x, cameraPosition.y);
     //vec2 BeePos;


    for (int i = 0; i < 4; ++i)
    {
        backimages[i].scrollOffset.x = backimages[i].scrollOffset.x + backimages[i].scrollSpeed.x   * _deltaTime;
        backimages[i].scrollOffset.y = backimages[i].scrollOffset.y + backimages[i].scrollSpeed.y   * _deltaTime;
        backimages[i].scroll.x = (cameraPosition.x * backimages[i].scrollRatio + backimages[i].scrollOffset.x) / backimages[i].tex->width;
        backimages[i].scroll.y = (cameraPosition.y * backimages[i].scrollRatio + backimages[i].scrollOffset.y) / backimages[i].tex->height;

    }

    for (Sprite* pIter : vSprites)
    {
        pIter->update(_deltaTime);

        //BeePos = pIter->getPosition();

    }

    //     vec2 CameraChange = vec2(BeePos.x - cameraPosition.x, BeePos.y - cameraPosition.y);
    //     CameraChange = CameraChange.normal(CameraChange);
    // 
    // 
    //     CameraChange = vec2(CameraChange.x * scrollSpeed.x * _deltaTime, CameraChange.y * scrollSpeed.y * _deltaTime);

        //cameraPosition = cameraPosition + CameraChange ;

//     vec2 CameraChange = cameraPosition;
//     cameraPosition = vec2(BeePos.x - WINDOW_WIDTH / 2, BeePos.y - WINDOW_HEIGHT / 2);
// 
//     CameraChange = cameraPosition - CameraChange;


}

void World::draw(const vec2& _screenSize)
{

    lgfx_clearcolorbuffer(clearRed, clearGreen, clearBlue);

    lgfx_setorigin(cameraPosition.x, cameraPosition.y);
    //lgfx_setcolor(0.f, 0.5f, 0.7f, 1.f);
    //lgfx_setblend(BLEND_ALPHA);

    //Nubes

    for (int i = 3; i >= 0; --i)
    {
        float u1 = backimages[i].scroll.x + _screenSize.x / backimages[i].tex->width;
        float v1 = backimages[i].scroll.y + _screenSize.y / backimages[i].tex->height;
        ltex_drawrotsized(backimages[i].tex, cameraPosition.x, cameraPosition.y, 0.f, 0.f, 0.f, _screenSize.x, _screenSize.y, backimages[i].scroll.x, backimages[i].scroll.y, u1, v1);

    }



    // lgfx_setcolor(1, 1, 1, 1);


     //u1 = _screenSize.x / pBackground2->width;


     //trees2
     //ltex_drawrotsized(pBackground2, 0.f, _screenSize.y / 2, 0.f, 0.f, 0.5f, _screenSize.x*2, pBackground2->height, p2u0, p2v0, p2u1, p2v1);


     //trees1
     //ltex_drawrotsized(pBackground1, _screenSize.x / 2, _screenSize.y / 2, 0.f, 0.5f, 0.5f, pBackground1->width, pBackground1->height, p1u0, p1v0, p1u1, p1v1);




 //     p0u0 = 500.f / pBackground0->width;
 //     p0v0 = 0.f;
 //     p0u1 = (_screenSize.x + 500.f) / pBackground0->width;
 //     p0v1 = 1.f;
 // 
 //     //level
 //     ltex_drawrotsized(pBackground0, 0.f, _screenSize.y / 2.f, 0.f, 0.f, 0.5f, _screenSize.x, pBackground0->height, p0u0, p0v0, p0u1, p0v1);
 // 



    for (Sprite* pIter : vSprites)
    {
        pIter->draw();
    }



}
