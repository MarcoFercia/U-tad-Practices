#include "Mesh.h"
#include "State.h"
#include "Material.h"
#include "Buffer.h"
#include "Shader.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

void Mesh::addBuffer(Buffer* _buffer, Material* _material)
{
    bufferVector.push_back(_buffer);
    materialsVector.push_back(_material);

}

size_t Mesh::getNumBuffers() const
{
    return bufferVector.size();
}

const Buffer* Mesh::GetBuffer(int _index) const
{
    if (_index < (bufferVector.size() - 1))
    {
        return bufferVector[_index];
    }
    return nullptr;
}

size_t Mesh::getNumMaterials() const
{
    return materialsVector.size();
}

const Material* Mesh::getMaerial(size_t _index) const
{
    if (_index < (materialsVector.size() - 1))
    {
        return materialsVector[_index];
    }
    return nullptr;
}

void Mesh::draw()
{

    size_t sizebuffer = bufferVector.size();

    for (size_t it = 0; it < sizebuffer; ++it)
    {
        materialsVector[it]->prepare();
        bufferVector[it]->Draw(materialsVector[it]->getShader());
     
    }


}
