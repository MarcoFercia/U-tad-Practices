#include "Material.h"
#include "Texture.h"
#include "Shader.h"
#include "State.h"
#include "Light.h"



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

glm::vec4 Material::getColor()
{
    return color;
}

void Material::setColor(glm::vec4 _color)
{
    color = _color;
}

uint8_t Material::getShininess()
{
    return shininess;
}

void Material::setShininess(uint8_t _shininess)
{
    shininess = _shininess;
}

void Material::prepare() 
{
    pTexture->bind();
    Shader* shaderRef = getShader();
    int locMPV = shaderRef->getLocation("mvp");
    shaderRef->setMatrix(locMPV, State::projectionMatrix * State::viewMatrix * State::modelMatrix);
    
    int locTexture = shaderRef->getLocation("texSampler");
    shaderRef->setInt(locTexture, 0);


    int locMV = shaderRef->getLocation("mv");
    glm::mat4 mv = State::viewMatrix * State::modelMatrix;
    shaderRef->setMatrix(locMV, mv);

    int locNormal = shaderRef->getLocation("nmatrix");
    glm::mat4 normMatrix = glm::inverse(mv);
    normMatrix = glm::transpose(normMatrix);
    shaderRef->setMatrix(locNormal, normMatrix);

    int NumberofLightsLoc = shaderRef->getLocation("numLights");
    shaderRef->setInt(NumberofLightsLoc, State::lights.size());

    int numOfLights = State::lights.size();
    for (int i = 0; i < numOfLights; ++i)
    {
        State::lights[i]->prepare(i, shaderRef);
    }

    int fNumberofLightsLoc = shaderRef->getLocation("_numLights");
    shaderRef->setInt(fNumberofLightsLoc, State::lights.size());


    int globalAmbientLoc = shaderRef->getLocation("_globalAmbient");
    shaderRef->setVec3(globalAmbientLoc, State::ambient);


    int MaterialAmbientLoc = shaderRef->getLocation("mat.ambient");
    shaderRef->setVec4(MaterialAmbientLoc, glm::vec4(color));

    int MaterialDiffuseLoc = shaderRef->getLocation("mat.diffuse");
    shaderRef->setVec4(MaterialDiffuseLoc, glm::vec4(color));

    int MaterialSpecularLoc = shaderRef->getLocation("mat.specular");
    shaderRef->setVec3(MaterialSpecularLoc, glm::vec3(color));

    int MaterialShininessLoc = shaderRef->getLocation("mat.shininess");
    shaderRef->setFloat(MaterialShininessLoc,shininess);

  
}
