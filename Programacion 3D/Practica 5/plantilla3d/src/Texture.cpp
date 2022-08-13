#include "Texture.h"



Texture* Texture::load(const char* _filename)
{
    Texture* pTexture = new Texture();
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pImage = stbi_load(_filename, &pTexture->textSize.x, &pTexture->textSize.y, nullptr, 4);
    glGenTextures(1, &pTexture->textId);
    glBindTexture(GL_TEXTURE_2D, pTexture->textId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pTexture->textSize.x, pTexture->textSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pImage);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(pImage);

    return pTexture;
}

Texture::Texture()
{

}

Texture::~Texture()
{

}

uint32_t Texture::getId() const
{
    return textId;
}

const glm::ivec2& Texture::getSize() const
{
    return textSize;
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, textId);
}


