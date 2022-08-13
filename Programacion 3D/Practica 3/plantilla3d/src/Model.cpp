#include "Model.h"
#include "State.h"
#include "Mesh.h"

Model::Model(Mesh& _mesh) : pMesh(&_mesh)
{

}

void Model::draw()
{
    State::modelMatrix = calculateModelMatrix();
    pMesh->draw();
}

void Model::update(float _deltaTime)
{
    vRotation.y += _deltaTime;
}

glm::mat4& Model::calculateModelMatrix()
{
    glm::mat4 Matrix = glm::mat4(1.0);
    Matrix = glm::translate(Matrix, vPosition);
    Matrix = glm::rotate(Matrix, vRotation.x, glm::vec3(1, 0, 0));
    Matrix = glm::rotate(Matrix, vRotation.y, glm::vec3(0, 1, 0));
    Matrix = glm::rotate(Matrix, vRotation.z, glm::vec3(0, 0, 1));
    Matrix = glm::scale(Matrix, vScale);
    return Matrix;
}
