#pragma once
//#include "../lib/glew/glew.c"
#include <cstdint>
#include <sstream>
//#include "../lib/glm/glm.hpp"
#include <GL/glew.h>
#include <glm.hpp>

class Shader
{

public:
    Shader(GLenum shaderType1, const std::string& filetext1, GLenum shaderType2, const std::string& filetext2);
    ~Shader();

    // Devuelve el identificador de OpenGL del programa
    uint32_t getId() const;


    // Obtiene el mensaje de error generado al compilar o enlazar
    const char* getError() const;


    // Activa el uso de este programa
    void use() const;


    // Activa la escritura de las variables attribute,
    // y especifica su formato
    void setupAttribs() const;


    // Obtiene la localización de una variable uniform
    int getLocation(const char* name) const;


    // Da valor a una variable uniform
    void setInt(int loc, int val);
    void setFloat(int loc, float val);
    void setVec3(int loc, const glm::vec3& vec);
    void setVec4(int loc, const glm::vec4& vec);
    void setMatrix(int loc, const glm::mat4& matrix);


private:
    //uint32_t Id;
    char* m_error;
    GLuint program;


public:
    GLint m_vposLoc;
    GLint m_vcolorLoc;
    GLint m_matrixLoc;
    GLint m_vTextureLoc;

};