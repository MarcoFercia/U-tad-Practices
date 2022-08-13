#include "Material.h"
#include "Texture.h"
#include "Shader.h"



Material::Material(Texture* _tex /*= nullptr*/, Shader* _shader /*= nullptr*/)
{
    pTexture = _tex;
    pShader = _shader;
}

// const Shader* Material::getShader() const
// {
//     return pShader;
// }

Shader* Material::getShader()
{
    if (pShader)
    {
        return pShader;
    }
    return State::defaultShader;
}

void Material::setShader(Shader* _shader)
{
    pShader = _shader;
}

const Texture* Material::getTexture() const
{
    return pTexture;
}

void Material::setTexture(Texture* _texture)
{
    pTexture = _texture;
}

void Material::prepare() 
{
    Shader* p = getShader();
    int locMPV = p->getLocation("mvp");
    getShader()->setMatrix(locMPV, State::projectionMatrix * State::viewMatrix * State::modelMatrix);
    pTexture->bind();
    int locTexture = getShader()->getLocation("texSampler");
    getShader()->setInt(locTexture, 0);

  
}
