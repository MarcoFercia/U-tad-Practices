#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define STB_IMAGE_IMPLEMENTATION

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
#include "Material.h"
#include "Texture.h"




#define RAD 0.01745329f
#define SCREEN_WIDTH 800.f
#define SCREEN_HEIGHT 600.f

int init();


const float FIXEDTICK = 1.f / 60.f;

double Time = 0;
double DeltaTime = 0;
double PreviousTime = 0;


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



     std::vector<Vertex> verticesTop
     {
 
 
         Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1, 1, 1), glm::vec2(0,0)),
         Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1, 1, 1), glm::vec2(1,0)),
         Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1, 1, 1),glm::vec2(1,1)),
         Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1, 1, 1), glm::vec2(0,1)),


         Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1, 1, 1), glm::vec2(1,1)),
         Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1, 1, 1), glm::vec2(0,1)),
         Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1, 1, 1),glm::vec2(0,0)),
         Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1, 1, 1),glm::vec2(1,0))
     };



     std::vector<IndexVex> indicesTop =
     {
        0,1,2,
        0,2,3,

        4,5,6,
        4,6,7
     };




    std::vector<Vertex> verticesSide
    {

        Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1, 1, 1), glm::vec2(0,1)),
        Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1, 1, 1), glm::vec2(1,1)),
        Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1, 1, 1),glm::vec2(0,0)),
        Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1, 1, 1), glm::vec2(1,0)),
        Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1, 1, 1), glm::vec2(0,1)),
        Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1, 1, 1), glm::vec2(0,0)),
        Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1, 1, 1),glm::vec2(1,1)),
        Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1, 1, 1),glm::vec2(1,0))

    };


    std::vector<IndexVex> indicesSide =
    {
       0,1,2,
       1,2,3,

       1,4,3,
       4,3,5,

       4,5,7,
       4,6,7,

       6,7,0,
       0,2,7
    };




    Camera* camera1 = new Camera();
    camera1->setClearColor(glm::vec3(0, 0, 0));
    camera1->setViewport(glm::ivec4(0, 0, 800, 600));
    camera1->setPosition(glm::vec3(0, 1, 3));
    world->addEntity(camera1);


    Mesh* triangleMesh = new Mesh();
    Buffer* buffTop = new Buffer(verticesTop, indicesTop);
    Buffer* buffSide = new Buffer(verticesSide, indicesSide);



    Material* MaterialSide = (new Material(Texture::load("data/front.png")));
    Material* MaterialTop = (new Material(Texture::load("data/top.png")));

    triangleMesh->addBuffer(buffTop, MaterialTop);
    triangleMesh->addBuffer(buffSide, MaterialSide);

    Model* modelbox = new Model(*triangleMesh);

    modelbox->setPosition(glm::vec3(0.f, 0.f, 0.f));
    modelbox->setScale(glm::vec3(1, 1, 1));
    modelbox->setRotation(glm::vec3(0, 0, 0));

    world->addEntity(modelbox);


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