#include "Mesh.h"
#include "State.h"

#include "Buffer.h"
#include "Shader.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

void Mesh::addBuffer(Buffer* _buffer, Shader* _shader)
{
    bufferVector.push_back(_buffer);
    ShaderVector.push_back(_shader);

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

void Mesh::draw()
{
//     for (int i = 0; i >= bufferVector.size() - 1; ++i)
//     {
//         if (ShaderVector[i] == nullptr)
//         {
//             State::defaultShader->use();
//             State::defaultShader->setupAttribs();
//         }
//         else
//         {
//             ShaderVector[i]->use();
//             ShaderVector[i]->setupAttribs();
//         }
// 
//         bufferVector[i]->Draw();
// 
//     }


    for (Buffer* it : bufferVector)
    {
        it->Draw();
    }


}
