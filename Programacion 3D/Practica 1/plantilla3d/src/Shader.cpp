#include "Shader.h"
#include "VertexVec.h"
#include <iosfwd>
#include "gtc/type_ptr.inl"
#include "GL/glew.h"

//#include "../lib/glm/gtc/type_ptr.hpp"




Shader::Shader(GLenum shaderType1, const char* filename1, GLenum shaderType2, const char* filename2)
{
    uint32_t  shaderid1 = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(shaderid1, 1, &filename1, nullptr);
    glCompileShader(shaderid1);

    GLint retCode1;

    glGetShaderiv(shaderid1, GL_COMPILE_STATUS, &retCode1);
    if (retCode1 == GL_FALSE)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shaderid1, sizeof(errorLog), nullptr, errorLog);
        m_error = errorLog;
        glDeleteShader(shaderid1);
        return;
    }

    GLuint shaderid2 = glCreateShader(shaderType2);
    glShaderSource(shaderid2, 1, &filename2, nullptr);
    glCompileShader(shaderid2);

    GLint retCode2;

    glGetShaderiv(shaderid1, GL_COMPILE_STATUS, &retCode2);
    if (retCode2 == GL_FALSE)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shaderid2, sizeof(errorLog), nullptr, errorLog);
        m_error = errorLog;
        glDeleteShader(shaderid2);
        return;
    }

    program = glCreateProgram();

    if (shaderid1)
    {
        glAttachShader(program, shaderid1);
    }


    if (shaderid2)
    {
        glAttachShader(program, shaderid2);
    }

    glLinkProgram(program);


    glDeleteShader(shaderid1);
    glDeleteShader(shaderid2);

    GLint retCode;

    glGetProgramiv(program, GL_LINK_STATUS, &retCode);
    if (retCode == GL_FALSE)
    {
        char errorLog[1024];
        glGetProgramInfoLog(program, sizeof(errorLog), nullptr, errorLog);
        m_error = errorLog;
        glDeleteProgram(program);
        program = 0;
        return;
    }

    m_vposLoc = glGetAttribLocation(program, "vpos");
    m_vcolorLoc = glGetAttribLocation(program, "vcolor");
    m_matrixLoc = glGetUniformLocation(program, "mvp");
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

uint32_t Shader::getId() const
{
    return program;
}

const char* Shader::getError() const
{
    return m_error;
}

void Shader::use() const
{
    glUseProgram(program);
}

void Shader::setupAttribs() const
{
    if (m_vposLoc != -1)
    {
        glEnableVertexAttribArray(m_vposLoc);
       glVertexAttribPointer(m_vposLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, position)));
    }

    if (m_vcolorLoc != -1)
    {
        glEnableVertexAttribArray(m_vcolorLoc);
       glVertexAttribPointer(m_vcolorLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, color)));
    }
}

int Shader::getLocation(const char* name) const
{
    return glGetAttribLocation(program, name);  
}

void Shader::setInt(int loc, int val)
{
    if (loc != -1)
    {
        glUniform1i(loc, val);
    }
}

void Shader::setFloat(int loc, float val)
{
    if (loc != -1)
    {
        glUniform1f(loc, val);
    }
}

void Shader::setVec3(int loc, const glm::vec3& vec)
{
    if (loc != -1)
    {
        glUniform3f(loc, vec.x, vec.y, vec.z);
    }
}

void Shader::setVec4(int loc, const glm::vec4& vec)
{
    if (loc != -1)
    {
        glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
    }
}

void Shader::setMatrix(int loc, const glm::mat4& matrix)
{
    if (loc != -1)
    {
        // GL_FLOAT
        glUniformMatrix4fv(loc, 1, false, glm::value_ptr(matrix));
    }
}

