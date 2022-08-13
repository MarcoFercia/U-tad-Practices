#pragma once

#include "State.h"

class Shader;
class Texture;

class Material
{
public:
    Material(Texture* _tex = nullptr, Shader* _shader = nullptr);


    //const Shader* getShader() const;
    Shader* getShader();

    void setShader(Shader* _shader);
    const Texture* getTexture() const;
    void setTexture(Texture* _texture);

    glm::vec4 getColor();
    void setColor(glm::vec4 _color);

    uint8_t getShininess();
    void setShininess(uint8_t _shininess);

    void prepare();

protected:

private:

    glm::vec4 color;
    uint8_t shininess;

    Shader* pShader;
    Texture* pTexture;
};

