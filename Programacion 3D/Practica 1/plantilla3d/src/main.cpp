#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <GL/glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/matrix_transform.hpp>
#include "detail/func_matrix.hpp"

#include <iostream>
//#include <vector>
//#include <iosfwd>
//#include <sstream>

#include "Shader.h"
#include <iosfwd>
#include <string>
#include <xiosbase>
#include <fstream>      // std::ifstream
#include <vector>
#include "VertexVec.h"
#include "Buffer.h"




#define RAD 0.01745329f
#define SCREEN_WIDTH 800.f
#define SCREEN_HEIGHT 600.f

int init();


const float FIXEDTICK = 1.f / 60.f;

double Time = 0;
double DeltaTime = 0;
double PreviousTime = 0;


// char* readfile(const char* filename)
// {
//     FILE* file = nullptr;
// 
//     if (!fopen_s(&file, filename, "r"))
//     {
//         fseek(file, 0, SEEK_END);
//         long size = ftell(file);
//         rewind(file);
// 
//         char* buff = new char[size];
//         if (fread(buff, 1, size, file))
//         {
//             fclose(file);
// 
//         }
//         return buff;
//     }
//     return nullptr;
// }





std::string readString(const std::string& filename)
{
    std::ifstream istream(filename.c_str(), std::ios_base::binary);
    std::stringstream sstream;
    sstream << istream.rdbuf();
    return sstream.str();
}



int main()
{
    init();


    // create window
      //glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_SAMPLES, 8);
    GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", nullptr, nullptr);
    if (!win)
    {
        std::cout << "could not create opengl window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(win);

    glewInit();



    std::string vertexShadername = readString("data/vertex.glsl");
    std::string fragmentShadername = readString("data/fragment.glsl");
    const  char* vertexShader  = vertexShadername.c_str();
    const  char* fragmentShader = fragmentShadername.c_str();
    Shader* shaderTriangles = new Shader(GL_VERTEX_SHADER, vertexShader, GL_FRAGMENT_SHADER, fragmentShader);


    std::vector<Vertex> vertices{ Vertex(glm::vec3(0.f, 0.5f,0.f),glm::vec3(1.f,1.f,1.f)),
                                  Vertex(glm::vec3(-0.5f,-0.5f,0.f),glm::vec3(1.f,1.f,1.f)),
                                  Vertex(glm::vec3(0.5f, -0.5f,0.f),glm::vec3(1.f,1.f,1.f))};


  

    std::vector<IndexVex> indices = { 0,1,2 };

    


    Buffer* bufferTriangle = new Buffer(vertices, indices);



  

   


    


    
    glm::mat4 modelmatrix1 = glm::mat4(1.f);
    modelmatrix1 = glm::translate(modelmatrix1, glm::vec3(-3.f, 0.f, 0.f));

    glm::mat4 modelmatrix2 = glm::mat4(1.f);
    modelmatrix2 = glm::translate(modelmatrix2, glm::vec3(-3.f, 0.f, -3.f));

    glm::mat4 modelmatrix3 = glm::mat4(1.f);
    modelmatrix3 = glm::translate(modelmatrix3, glm::vec3(-3.f, 0.f, -6.f));

    glm::mat4 modelmatrix4 = glm::mat4(1.f);
    modelmatrix4 = glm::translate(modelmatrix4, glm::vec3(0.f, 0.f, 0.f));

    glm::mat4 modelmatrix5 = glm::mat4(1.f);
    modelmatrix5 = glm::translate(modelmatrix5, glm::vec3(0.f, 0.f, -3.f));

    glm::mat4 modelmatrix6 = glm::mat4(1.f);
    modelmatrix6 = glm::translate(modelmatrix6, glm::vec3(0.f, 0.f, -6.f));

    glm::mat4 modelmatrix7 = glm::mat4(1.f);
    modelmatrix7 = glm::translate(modelmatrix7, glm::vec3(3.f, 0.f, 0.f));

    glm::mat4 modelmatrix8 = glm::mat4(1.f);
    modelmatrix8 = glm::translate(modelmatrix8, glm::vec3(3.f, 0.f, -3.f));

    glm::mat4 modelmatrix9 = glm::mat4(1.f);
    modelmatrix9 = glm::translate(modelmatrix9, glm::vec3(3.f, 0.f, -6.f));
    
   

    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0, 0, 6), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    glm::mat4 projectMatrix = glm::perspective(float(glm::radians(60.f)), float((SCREEN_WIDTH / SCREEN_HEIGHT)), (0.1f), (100.f));

    glm::mat4 mvp = glm::mat4(1.f);



    PreviousTime = glfwGetTime();

    // main loop
    while (!glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE))
    {
        // get window size
        int screenWidth, screenHeight;
        glfwGetWindowSize(win, &screenWidth, &screenHeight);

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        DeltaTime += glfwGetTime() - PreviousTime;
        PreviousTime = glfwGetTime();


        
        while (DeltaTime >= FIXEDTICK)
        {
            DeltaTime -= FIXEDTICK;                    
       
            modelmatrix1 = glm::rotate(modelmatrix1, glm::radians((32 * RAD)), glm::vec3(0.f, 1.f, 0.f));      
                         
            modelmatrix2 = glm::rotate(modelmatrix2, glm::radians((32 * RAD)), glm::vec3(0.f, 1.f, 0.f));                   
            
            modelmatrix3 = glm::rotate(modelmatrix3, glm::radians((32 * RAD)), glm::vec3(0.f, 1.f, 0.f));                                    
         
            modelmatrix4 = glm::rotate(modelmatrix4, glm::radians((32 * RAD)), glm::vec3(0.f, 1.f, 0.f));                           
           
            modelmatrix5 = glm::rotate(modelmatrix5, glm::radians((32 * RAD)), glm::vec3(0.f, 1.f, 0.f));                
           
            modelmatrix6 = glm::rotate(modelmatrix6, glm::radians((32 * RAD)), glm::vec3(0.f, 1.f, 0.f));                       
     
            modelmatrix7 = glm::rotate(modelmatrix7, glm::radians((32 * RAD)), glm::vec3(0.f, 1.f, 0.f));                               
        
            modelmatrix8 = glm::rotate(modelmatrix8, glm::radians((32 * RAD)), glm::vec3(0.f, 1.f, 0.f));          
          
            modelmatrix9 = glm::rotate(modelmatrix9, glm::radians((32 * RAD)), glm::vec3(0.f, 1.f, 0.f));     
        
        
        }

        mvp = projectMatrix * viewMatrix * modelmatrix1;
        shaderTriangles->setMatrix(0, mvp);
        bufferTriangle->Draw(*shaderTriangles);

        mvp = projectMatrix * viewMatrix * modelmatrix2;
        shaderTriangles->setMatrix(0, mvp);
        bufferTriangle->Draw(*shaderTriangles);

        mvp = projectMatrix * viewMatrix * modelmatrix3;
        shaderTriangles->setMatrix(0, mvp);
        bufferTriangle->Draw(*shaderTriangles);

        mvp = projectMatrix * viewMatrix * modelmatrix4;
        shaderTriangles->setMatrix(0, mvp);
        bufferTriangle->Draw(*shaderTriangles);

        mvp = projectMatrix * viewMatrix * modelmatrix5;
        shaderTriangles->setMatrix(0, mvp);
        bufferTriangle->Draw(*shaderTriangles);

        mvp = projectMatrix * viewMatrix * modelmatrix6;
        shaderTriangles->setMatrix(0, mvp);
        bufferTriangle->Draw(*shaderTriangles);

        mvp = projectMatrix * viewMatrix * modelmatrix7;
        shaderTriangles->setMatrix(0, mvp);
        bufferTriangle->Draw(*shaderTriangles);

        mvp = projectMatrix * viewMatrix * modelmatrix8;
        shaderTriangles->setMatrix(0, mvp);
        bufferTriangle->Draw(*shaderTriangles);

        mvp = projectMatrix * viewMatrix * modelmatrix9;
        shaderTriangles->setMatrix(0, mvp);
        bufferTriangle->Draw(*shaderTriangles);






        // refresh screen
        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    // shutdown
    glfwTerminate();
}


int init()
{
    // init glfw
    if (!glfwInit())
    {
        std::cout << "could not initialize glfw" << std::endl;
        return -1;
    }



    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);

   
    return 0;
}