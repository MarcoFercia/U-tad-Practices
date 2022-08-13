#pragma once
#include "Entity.h"


class Camera : public Entity
{

public:

    Camera();
    ~Camera();

public:

protected:

private:

public:

    const glm::mat4& getProjection() const;
    const glm::ivec4& getViewport() const;
    const glm::vec3& getClearColor() const;

    void setProjection(const glm::mat4& _proj);
    void setViewport(const glm::ivec4& _vp);
    void setClearColor(const glm::vec3& _color);
    void setLookPoint(const glm::vec3& _direction);

    void prepare();
protected:

private:

    glm::mat4 mProjection;
    glm::ivec4 vViewport;
    glm::vec3 vColor;
    glm::vec3 lookPoint;
};

