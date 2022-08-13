#include "World.h"
#include "sreensize.h"
#include "pugixml.cpp"
#include <iostream>
#include"stb_image.h"

//#define STB_IMAGE_IMPLEMENTATION

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
        backimages[_layer].scrollSpeed = _speed;
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


    for (int i = 0; i < 4; ++i)
    {
        if (backimages[i].tex)
        {
            backimages[i].scrollOffset.x = backimages[i].scrollOffset.x + backimages[i].scrollSpeed.x * _deltaTime;
            backimages[i].scrollOffset.y = backimages[i].scrollOffset.y + backimages[i].scrollSpeed.y * _deltaTime;
            backimages[i].scroll.x = (cameraPosition.x * backimages[i].scrollRatio + backimages[i].scrollOffset.x) / backimages[i].tex->width;
            backimages[i].scroll.y = (cameraPosition.y * backimages[i].scrollRatio + backimages[i].scrollOffset.y) / backimages[i].tex->height;
        }
    }

    for (Sprite* pIter : vSprites)
    {
        pIter->update(_deltaTime);


    }

}

void World::draw(const vec2& _screenSize)
{

    lgfx_clearcolorbuffer(clearRed, clearGreen, clearBlue);

    lgfx_setorigin(cameraPosition.x, cameraPosition.y);
    lgfx_setblend(BLEND_ALPHA);
    //Nubes

    for (int i = 3; i >= 0; --i)
    {
        if (backimages[i].tex)
        {
            float u1 = backimages[i].scroll.x + _screenSize.x / backimages[i].tex->width;
            float v1 = backimages[i].scroll.y + _screenSize.y / backimages[i].tex->height;
            ltex_drawrotsized(backimages[i].tex, cameraPosition.x, cameraPosition.y, 0.f, 0.f, 0.f, _screenSize.x, _screenSize.y, backimages[i].scroll.x, backimages[i].scroll.y, u1, v1);
        }

    }

    for (Sprite* pIter : vSprites)
    {
        pIter->draw();
    }

}


void World::setScreenSize(vec2 _screenSize)
{
    ScreenSize = _screenSize;
}

vec2 World::getMapSize() const
{
    return mapSize;
}


inline std::string extractPath(const std::string& filename) {
    std::string filenameCopy = filename;
    while (filenameCopy.find("\\") != std::string::npos) {
        filenameCopy.replace(filenameCopy.find("\\"), 1, "/");
    }
    filenameCopy = filenameCopy.substr(0, filenameCopy.rfind('/'));
    if (filenameCopy.size() > 0) filenameCopy += "/";
    return filenameCopy;
}



ltex_t* loadTex(const char* filename)
{
    int ximage = 0, yimage = 0;
    unsigned char* pPtr = stbi_load(filename, &ximage, &yimage, nullptr, 4);
    ltex_t* pLtex = ltex_alloc(ximage, yimage, 1);
    ltex_setpixels(pLtex, pPtr);
    stbi_image_free(pPtr);

    return pLtex;
}


bool World::loadMap(const char* _filename, uint16_t _firstColId)
{
    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file(_filename);

    if (result)
    {
        pugi::xml_node mapNode = document.child("map");

        mapSize.x = mapNode.attribute("width").as_int();
        mapSize.y = mapNode.attribute("height").as_int();

        vec2 tileSize = vec2(mapNode.attribute("tilewidth").as_int(), mapNode.attribute("tileheight").as_int());


        vec2 tileFrames;
        tileFrames.x = mapNode.child("tileset").attribute("columns").as_int();
        tileFrames.y = mapNode.child("tileset").attribute("tilecount").as_int() / tileFrames.x;

        std::string textureImage = extractPath(_filename) + mapNode.child("tileset").child("image").attribute("source").as_string();
        const ltex_t* tileSet = loadTex(textureImage.c_str());

        float adaptableX = ScreenSize.x / (mapSize.x * mapSize.y);
        float adaptableY = ScreenSize.y / (mapSize.x * mapSize.y);

        vec2 scaleTile = vec2(adaptableX, adaptableY);
        vec2 offset = vec2(tileSize.x * scaleTile.x, tileSize.y * scaleTile.y);

        int counter = 0;

        for (pugi::xml_node tileNode = mapNode.child("layer").child("data").child("tile");
            tileNode;
            tileNode = tileNode.next_sibling("tile"))
        {
            int gid = tileNode.attribute("gid").as_int();

            if (gid != 0)
            {
                Sprite* tile = new Sprite(tileSet, tileFrames.x, tileFrames.y);
                tile->setCurrentFrame(gid - _firstColId);
                tile->setPosition(vec2((0.5f + counter % int(mapSize.x)) * offset.x, (0.5f + int(counter / int(mapSize.x))) * offset.y));
                
                tile->setScale(scaleTile);
                tile->setCollisionType(Sprite::CollisionType::COLLISION_RECT);


                vSprites.push_back(tile);
            }
            counter++;
        }


        float ratio = mapSize.y / mapSize.x;
        mapSize.x = ScreenSize.x;
        mapSize.y = ScreenSize.x * ratio;
        return true;
    }
    else
    {
        std::cout << result.description() << std::endl;
        return false;
    }

}



bool World::moveSprite(Sprite& _sprite, const vec2& _amount)
{
    bool collide = false;

    vec2 InitPos = _sprite.getPosition();
    _sprite.setPosition(vec2(InitPos.x + _amount.x, InitPos.y));

    for (Sprite* it : vSprites)
    {
       // if (&_sprite != it)
       // {
            if (_sprite.collides(*it))
            {
                _sprite.setPosition(InitPos);
                collide = true;
                break;
            }
        //}
        
    }

    _sprite.setPosition(vec2(_sprite.getPosition().x, _sprite.getPosition().y + _amount.y));

    for (Sprite* it : vSprites)
    {
       // if (&_sprite != it)
       // {
            if (_sprite.collides(*it))
            {
                _sprite.setPosition(vec2(_sprite.getPosition().x, InitPos.y));
                collide = true;
                break;
            }
       // }
      
    }
    return collide;

}
