#include "Camera.h"
#include "GL/glew.h"
#include "State.h"

Camera::Camera() : Entity()
{

}

Camera::~Camera()
{

}

const glm::mat4& Camera::getProjection() const
{
    return mProjection;
}

const glm::ivec4& Camera::getViewport() const
{
    return vViewport;
}

const glm::vec3& Camera::getClearColor() const
{
    return vColor;
}

void Camera::setProjection(const glm::mat4& _proj)
{
    mProjection = _proj;
}

void Camera::setViewport(const glm::ivec4& _vp)
{
    vViewport = _vp;
}

void Camera::setClearColor(const glm::vec3& _color)
{
    vColor = _color;
}

void Camera::prepare()
{
    glViewport(vViewport.x, vViewport.y, vViewport.z, vViewport.w);
    glScissor(vViewport.x, vViewport.y, vViewport.z, vViewport.w);
    glClearColor(vColor.r, vColor.g, vColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT /*| GL_STENCIL_BUFFER_BIT*/);

    State::viewMatrix = glm::lookAt(glm::vec3(0, 0, 6), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    State::projectionMatrix = glm::perspective(45.f, 800.f / 600.f, 0.1f, 100.f);

}
