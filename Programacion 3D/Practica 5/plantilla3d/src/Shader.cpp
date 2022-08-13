#include "Shader.h"
#include "VertexVec.h"
#include <iosfwd>
#include "gtc/type_ptr.inl"
#include "GL/glew.h"
#include <fstream>  
//#include "../lib/glm/gtc/type_ptr.hpp"

std::string readString(const std::string& filename)
{
    std::ifstream istream(filename.c_str(), std::ios_base::binary);
    std::stringstream sstream;
    sstream << istream.rdbuf();
    return sstream.str();
}



Shader::Shader(GLenum shaderType1, const std::string& filetext1, GLenum shaderType2, const std::string& filetext2)
{


    std::string vertexShadername = readString(filetext1);
    std::string fragmentShadername = readString(filetext2);
    const  char* filename1  = vertexShadername.c_str();
    const  char* filename2 = fragmentShadername.c_str();


    uint32_t  shaderid1 = glCreateShader(shaderType1);

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

    glGetShaderiv(shaderid2, GL_COMPILE_STATUS, &retCode2);
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
    //m_vcolorLoc = glGetAttribLocation(program, "vcolor");
    m_vNormalLoc = glGetAttribLocation(program, "vnormal");
    m_vTextureLoc = glGetAttribLocation(program, "vtex");



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
    use();

    if (m_vposLoc != -1)
    {
        glEnableVertexAttribArray(m_vposLoc);
       glVertexAttribPointer(m_vposLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, position)));
    }


    if (m_vTextureLoc != -1)
    {
        glEnableVertexAttribArray(m_vTextureLoc);
        glVertexAttribPointer(m_vTextureLoc, 2, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, textCoord)));
    }

    if (m_vNormalLoc != -1)
    {
        glEnableVertexAttribArray(m_vNormalLoc);
        glVertexAttribPointer(m_vNormalLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, normal)));

    }

}

int Shader::getLocation(const char* name) const
{
    return glGetUniformLocation(program, name);
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

void Shader::setVec2(int loc, const glm::vec2& vec)
{
    if (loc != -1)
    {
        glUniform2f(loc, vec.x, vec.y);
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
        glUniformMatrix4fv(loc, 1, false, glm::value_ptr(matrix));
    }
}

