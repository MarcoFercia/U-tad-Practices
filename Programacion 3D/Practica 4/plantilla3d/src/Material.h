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
    void prepare();

protected:

private:

    Shader* pShader;
    Texture* pTexture;
};

