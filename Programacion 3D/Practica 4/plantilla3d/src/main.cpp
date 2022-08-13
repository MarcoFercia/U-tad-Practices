#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define STB_IMAGE_IMPLEMENTATION
/*#define TINYOBJLOADER_IMPLEMENTATION*/

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
float cameraSpeed=10.f;


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





    Camera* camera1 = new Camera();
    camera1->setClearColor(glm::vec3(0, 0, 0));
    camera1->setViewport(glm::ivec4(0, 0, 800, 600));
    camera1->setPosition(glm::vec3(8, 1, 58));
    camera1->setLookPoint(glm::vec3(0,0,-1));
    world->addEntity(camera1);


  
    Mesh* box = Mesh::load("data/box_stack.obj");
    Model* boxModel = new Model(*box);
    boxModel->setPosition(glm::vec3(-7, 0, 2));
    boxModel->setScale(glm::vec3(3, 3, 3));
    boxModel->setRotation(glm::vec3(0, 0, 0));
    world->addEntity(boxModel);


    Mesh* gunslinger = Mesh::load("data/gunslinger.obj");
    Model* gunslingerModel = new Model(*gunslinger);
    gunslingerModel->setPosition(glm::vec3(7, 0, 2));
    gunslingerModel->setScale(glm::vec3(1, 1, 1));
    gunslingerModel->setRotation(glm::vec3(0, 0, 0));
    world->addEntity(gunslingerModel);






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


        glm::vec3 tempvec(0, 0, 0);
        if (glfwGetKey(win, GLFW_KEY_RIGHT))
        {
            tempvec.x += 1;
        }
        else if (glfwGetKey(win, GLFW_KEY_LEFT))
        {
            tempvec.x -= 1;
        }
        if (glfwGetKey(win, GLFW_KEY_UP))
        {
            tempvec.z -= 1;
        }
        else if (glfwGetKey(win, GLFW_KEY_DOWN))
        {
            tempvec.z += 1;
        }

        tempvec = tempvec * cameraSpeed * FIXEDTICK;
        camera1->move(tempvec);








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