#include "Light.h"
#include <string>
#include "Shader.h"

Light::Light() : myType(lightType::Directional), color(0.f, 0.f, 0.f,0.f)
{

}

Light::~Light()
{

}

lightType Light::getType()
{
    return myType;
}

void Light::setType(lightType _type)
{
    myType = _type;
    color.w = int(_type);
}

const glm::vec3& Light::getColor() const
{
    return color;
}

void Light::setColor(const glm::vec3 _color)
{
    color.x = _color.x;
    color.y = _color.y;
    color.z = _color.z;
}

float Light::getLinearAttenuation() const
{
    return linearAttenuation;
}

void Light::setLinearAtteniation(float _attenuation)
{
    linearAttenuation = _attenuation;
}

void Light::prepare(int _index, Shader* _shader) const
{
    std::string light = "lights[";
    std::string ambient = "].ambient";
    std::string diffuse = "].diffuse";
    std::string specular = "].specular";
    std::string position = "].position";
   // std::string lightInfoString = "].lightInfo";
    std::string boolPoint = "].boolPointLight";
    std::string sAttenuation = "].linearAttenuation";
    std::string index = std::to_string(_index);

    
        int ambientLocation = _shader->getLocation((light + index + ambient).c_str()); 
        _shader->setVec4(ambientLocation,color);

        int diffuseLocation = _shader->getLocation((light + index + diffuse).c_str());
        _shader->setVec4(diffuseLocation,color);

        int specularLocation = _shader->getLocation((light + index + specular).c_str());
        _shader->setVec4(specularLocation, color);

        int positionLocation = _shader->getLocation((light + index + position).c_str());
        _shader->setVec3(positionLocation, vPosition);

        
        
        int typevalue;
        if (myType == lightType::Point)
        {
            typevalue = 1;
        }
        else
        {
            typevalue = 0;
        }



        int locboolPointLight = _shader->getLocation((light + index + boolPoint).c_str());
        _shader->setFloat(locboolPointLight,typevalue);

        int attenuationLoc = _shader->getLocation((light + index + sAttenuation).c_str());
        _shader->setFloat(attenuationLoc, linearAttenuation);     

 
}
