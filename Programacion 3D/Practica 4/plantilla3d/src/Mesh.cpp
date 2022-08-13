#define TINYOBJLOADER_IMPLEMENTATION

#include "Mesh.h"
#include "State.h"
#include "Material.h"
#include "Buffer.h"
#include "Shader.h"
#include <tiny_obj_loader.h>
#include "Texture.h"



Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

Mesh* Mesh::load(const char* _filename, const Shader* _shader /*= nullptr*/)
{
    Mesh* mesh = new Mesh();

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, _filename, "data"))
    {
        return nullptr;
    }

    for (unsigned int i = 0; i < shapes.size(); ++i)
    {
        std::string root = "data/";
        std::vector<Vertex> vVertex;
        std::vector<IndexVex> vIndexVertex;

        for (unsigned int y = 0; y < shapes[i].mesh.indices.size(); ++y)
        {
            Vertex* vertexTemp = new Vertex();
            vertexTemp->position.x = attrib.vertices[3 * shapes[i].mesh.indices[y].vertex_index + 0];
            vertexTemp->position.y = attrib.vertices[3 * shapes[i].mesh.indices[y].vertex_index + 1];
            vertexTemp->position.z = attrib.vertices[3 * shapes[i].mesh.indices[y].vertex_index + 2];
            vertexTemp->color.r = 1;
            vertexTemp->color.g = 1;
            vertexTemp->color.b = 1;
            vertexTemp->textCoord.x = attrib.texcoords[2 * shapes[i].mesh.indices[y].texcoord_index + 0];
            vertexTemp->textCoord.y = attrib.texcoords[2 * shapes[i].mesh.indices[y].texcoord_index + 1];
            vVertex.push_back(*vertexTemp);
            vIndexVertex.push_back(y);
        
        }
        Buffer* buff = new Buffer(vVertex, vIndexVertex);
        root = root.append(materials[i].ambient_texname);
        Material* material = new Material(Texture::load(root.c_str()));
        mesh->addBuffer(buff, material);
    }



    return mesh;
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
