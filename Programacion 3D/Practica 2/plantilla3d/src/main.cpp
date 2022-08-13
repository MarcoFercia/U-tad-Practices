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
#include "State.h"
#include "Camera.h"
#include "World.h"
#include "Mesh.h"
#include "Model.h"




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








int main()
{

    // init glfw
    if (!glfwInit()) {
        std::cout << "could not initialize glfw" << std::endl;
        return -1;
    }
   
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

    init();
 
    World* world = new World();



    std::vector<Vertex> vertices{ Vertex(glm::vec3(0.f, 0.5f,0.f),glm::vec3(1.f,0.f,0.f)),
                                  Vertex(glm::vec3(-0.5f,-0.5f,0.f),glm::vec3(0.f,1.f,0.f)),
                                  Vertex(glm::vec3(0.5f, -0.5f,0.f),glm::vec3(0.f,0.f,1.f)) };




    std::vector<IndexVex> indices = { 0,1,2 };



    Camera* camera1 = new Camera();
    camera1->setClearColor(glm::vec3(0, 0, 0));
    camera1->setViewport(glm::ivec4(0, 0, 800, 600));
    camera1->setPosition(glm::vec3(0, 0, 6));
    world->addEntity(camera1);


    Mesh* triangleMesh = new Mesh();
    Buffer* buff = new Buffer(vertices, indices);
    buff->setPosition(glm::vec3(-3.f,0.f,0.f));
    triangleMesh->addBuffer(buff);


     Model* modeltriangle = new Model(*triangleMesh);
    modeltriangle->setPosition(glm::vec3(-3.f, 0.f, 0.f));
    modeltriangle->setScale(glm::vec3(1.f, 1.f, 1.f));
    modeltriangle->setRotation(glm::vec3(0.f, 0.f, 0.f));
    world->addEntity(modeltriangle);

    modeltriangle = new Model(*triangleMesh);
    modeltriangle->setPosition(glm::vec3(-3.f, 0.f, -3.f));
    modeltriangle->setScale(glm::vec3(1.f, 1.f, 1.f));
    modeltriangle->setRotation(glm::vec3(0.f, 0.f, 0.f));
    world->addEntity(modeltriangle);

    modeltriangle = new Model(*triangleMesh);
    modeltriangle->setPosition(glm::vec3(-3.f, 0.f, -6.f));
    modeltriangle->setScale(glm::vec3(1.f, 1.f, 1.f));
    modeltriangle->setRotation(glm::vec3(0.f, 0.f, 0.f));
    world->addEntity(modeltriangle);

    modeltriangle = new Model(*triangleMesh);
    modeltriangle->setPosition(glm::vec3(0.f, 0.f, 0.f));
    modeltriangle->setScale(glm::vec3(1.f, 1.f, 1.f));
    modeltriangle->setRotation(glm::vec3(0.f, 0.f, 0.f));
    world->addEntity(modeltriangle);

    modeltriangle = new Model(*triangleMesh);
    modeltriangle->setPosition(glm::vec3(0.f, 0.f, -3.f));
    modeltriangle->setScale(glm::vec3(1.f, 1.f, 1.f));
    modeltriangle->setRotation(glm::vec3(0.f, 0.f, 0.f));
    world->addEntity(modeltriangle);

    modeltriangle = new Model(*triangleMesh);
    modeltriangle->setPosition(glm::vec3(0.f, 0.f, -6.f));
    modeltriangle->setScale(glm::vec3(1.f, 1.f, 1.f));
    modeltriangle->setRotation(glm::vec3(0.f, 0.f, 0.f));
    world->addEntity(modeltriangle);

    modeltriangle = new Model(*triangleMesh);
    modeltriangle->setPosition(glm::vec3(3.f, 0.f, 0.f));
    modeltriangle->setScale(glm::vec3(1.f, 1.f, 1.f));
    modeltriangle->setRotation(glm::vec3(0.f, 0.f, 0.f));
    world->addEntity(modeltriangle);

    modeltriangle = new Model(*triangleMesh);
    modeltriangle->setPosition(glm::vec3(3.f, 0.f, -3.f));
    modeltriangle->setScale(glm::vec3(1.f, 1.f, 1.f));
    modeltriangle->setRotation(glm::vec3(0.f, 0.f, 0.f));
    world->addEntity(modeltriangle);

    modeltriangle = new Model(*triangleMesh);
    modeltriangle->setPosition(glm::vec3(3.f, 0.f, -6.f));
    modeltriangle->setScale(glm::vec3(1.f, 1.f, 1.f));
    modeltriangle->setRotation(glm::vec3(0.f, 0.f, 0.f));
    world->addEntity(modeltriangle);




    PreviousTime = glfwGetTime();

    // main loop
    while (!glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE))
    {
        // get window size
        int screenWidth, screenHeight;
        glfwGetWindowSize(win, &screenWidth, &screenHeight);

       
        DeltaTime += glfwGetTime() - PreviousTime;
        PreviousTime = glfwGetTime();



        while (DeltaTime >= FIXEDTICK)
        {
            DeltaTime -= FIXEDTICK;

            world->update(FIXEDTICK);

        }

        world->draw();





        // refresh screen
        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    // shutdown
    glfwTerminate();
}


int init()
{

    glewInit();


    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);


    State::defaultShader = new Shader(GL_VERTEX_SHADER, "data/vertex.glsl", GL_FRAGMENT_SHADER, "data/fragment.glsl");


    return 0;
}