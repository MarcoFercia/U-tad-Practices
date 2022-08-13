#pragma once
#include "Entity.h"


class Mesh;

class Model: public Entity
{
public:

    Model(Mesh& mesh);

public:

protected:

private:

public:

    virtual void draw() override;
    virtual void update(float _deltaTime) override;


protected:

private:

    glm::mat4& calculateModelMatrix();

    Mesh* pMesh;


};

