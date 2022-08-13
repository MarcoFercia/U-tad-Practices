#pragma once
#include "stb_image.h"
#include <glm.hpp>
#include "GL/glew.h"

class Texture
{
public:

    static Texture* load(const char* _filename);

    uint32_t getId() const;

    const glm::ivec2& getSize() const;

    void bind() const;




protected:

private:

    Texture();
    ~Texture();


    uint32_t textId;
    glm::ivec2 textSize;




};

