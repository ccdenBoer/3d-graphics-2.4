#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

void init();
void update();
void draw();
std::vector<Vertex> createCube(float x, float y, float z);
std::vector<Vertex> rotateCube(std::vector<Vertex> vertices, float angleX, float angleY, float angleZ);

float camval1 = 1;
float camval2 = 1;
float camval3 = 5;
float camval4 = 0;
float camval5 = 0;
float camval6 = 0;
float camval7 = 0;
float camval8 = 1;
float camval9 = 0;

float rotation1 = 0;
float rotation2 = 0;
float rotation3 = 0;

float posx = 0;
float posy = 0;

static std::vector<Vertex> vbo1 = createCube(0, 0, 0);
static std::vector<Vertex> vbo2 = createCube(-2, 0, 0);
static std::vector<Vertex> vbo3 = createCube(2, 0, 0);

static bool mode = false;

int main(void)
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);

    tigl::init();

    init();

	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();


    return 0;
}


void init()
{
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            
            if (key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(window, true);
            if (key == GLFW_KEY_LEFT_SHIFT) {
                camval1 = 1;
                camval2 = 1;
                camval3 = 5;
                camval4 = 0;
                camval5 = 0;
                camval6 = 0;
                camval7 = 0;
                camval8 = 1;
                camval9 = 0;
            }
            if (key == GLFW_KEY_RIGHT_CONTROL) {
                if (mode)
                    mode = false;
                else
                    mode = true;
            }

            if (key == GLFW_KEY_UP) {
                posy += 0.1;
            }
            if (key == GLFW_KEY_DOWN) {
                posy -= 0.1;
            }
            if (key == GLFW_KEY_RIGHT) {
                posx += 0.1;
            }
            if (key == GLFW_KEY_LEFT) {
                posx -= 0.1;
            }
    });

}


void update()
{
    rotation1 += 0.5;
    rotation2 += 0.5;
    rotation3 += 0.5;
    if (rotation1 > 360) {
        rotation1 = 0;
        rotation2 = 0;
        rotation3 = 0;
    }
    vbo1 = createCube(posx, posy, 0);
}

void draw()
{
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(mode)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 100.0f);

    tigl::shader->setProjectionMatrix(projection);
    tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(camval1, camval2, camval3), glm::vec3(camval4, camval5, camval6), glm::vec3(camval7, camval8, camval9)));
    tigl::shader->setModelMatrix(glm::mat4(1.0f));

    tigl::shader->enableColor(true);
    tigl::shader->enableLighting(true);
    tigl::shader->setLightCount(1);
    tigl::shader->setLightDirectional(0, true);
    tigl::shader->setLightPosition(0, glm::vec3(10, 10, 10));
    tigl::shader->setLightAmbient(0, glm::vec3(0.1f, 0.1f, 0.15f));
    tigl::shader->setLightDiffuse(0, glm::vec3(0.8f, 0.8f, 0.8f));
    tigl::shader->setLightSpecular(0, glm::vec3(0, 0, 0));
    tigl::shader->setShinyness(32.0f);
    tigl::shader->setFogLinear(0, 50);
    tigl::shader->enableColorMult(false);
    tigl::shader->enableFog(true);

    glEnable(GL_DEPTH_TEST);
    
    

    tigl::drawVertices(GL_QUADS, rotateCube(vbo1, 0, rotation1, 0));
    tigl::drawVertices(GL_QUADS, rotateCube(vbo2, rotation2, 0, 0));
    tigl::drawVertices(GL_QUADS, rotateCube(vbo3, 0, 0, rotation3));

}

// Function to create a cube using a vector of vertices
std::vector<Vertex> createCube(float x, float y, float z)
{
    std::vector<Vertex> vertices;

    // Vertex positions
    glm::vec3 p0(-0.5f + x, -0.5f + y, 0.5f + z); // front bottom left
    glm::vec3 p1(0.5f + x, -0.5f + y, 0.5f + z); // front bottom right
    glm::vec3 p2(0.5f + x, 0.5f + y, 0.5f + z); // front top right
    glm::vec3 p3(-0.5f + x, 0.5f + y, 0.5f + z); // front top left
    glm::vec3 p4(-0.5f + x, -0.5f + y, -0.5f + z); // back bottom left
    glm::vec3 p5(0.5f + x, -0.5f + y, -0.5f + z); // back bottom right
    glm::vec3 p6(0.5f + x, 0.5f + y, -0.5f + z); // back top right
    glm::vec3 p7(-0.5f + x, 0.5f + y, -0.5f + z); // back top left

    // Vertex normals
    glm::vec3 n0(0.0f + x, 0.0f + y, 1.0f + z); // front
    glm::vec3 n1(1.0f + x, 0.0f + y, 0.0f + z); // right
    glm::vec3 n2(0.0f + x, 0.0f + y, -1.0f + z); // back
    glm::vec3 n3(-1.0f + x, 0.0f + y, 0.0f + z); // left
    glm::vec3 n4(0.0f + x, 1.0f + y, 0.0f + z); // top
    glm::vec3 n5(0.0f + x, -1.0f + y, 0.0f + z); // bottom

    // Vertex texture coordinates
    glm::vec2 t0(0.0f, 0.0f);
    glm::vec2 t1(1.0f, 0.0f);
    glm::vec2 t2(1.0f, 1.0f);
    glm::vec2 t3(0.0f, 1.0f);

    // Add vertices for the front face
    vertices.push_back(Vertex(p0, n0, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), t0));
    vertices.push_back(Vertex(p1, n0, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), t1));
    vertices.push_back(Vertex(p2, n0, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), t2));
    vertices.push_back(Vertex(p3, n0, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), t3));

    // Add vertices for the back face
    vertices.push_back(Vertex(p4, n1, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), t0));
    vertices.push_back(Vertex(p5, n1, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), t1));
    vertices.push_back(Vertex(p6, n1, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), t2));
    vertices.push_back(Vertex(p7, n1, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), t3));

    // Add vertices for the left face
    vertices.push_back(Vertex(p4, n2, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), t0));
    vertices.push_back(Vertex(p0, n2, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), t1));
    vertices.push_back(Vertex(p3, n2, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), t2));
    vertices.push_back(Vertex(p7, n2, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), t3));

    // Add vertices for the right face
    vertices.push_back(Vertex(p1, n3, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), t0));
    vertices.push_back(Vertex(p5, n3, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), t1));
    vertices.push_back(Vertex(p6, n3, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), t2));
    vertices.push_back(Vertex(p2, n3, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), t3));

    // Add vertices for the top face
    vertices.push_back(Vertex(p4, n3, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), t1));
    vertices.push_back(Vertex(p5, n3, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), t2));
    vertices.push_back(Vertex(p6, n3, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), t3));
    vertices.push_back(Vertex(p7, n3, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), t0));

    // Add vertices for the bottom face
    vertices.push_back(Vertex(p0, n4, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), t1));
    vertices.push_back(Vertex(p3, n4, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), t2));
    vertices.push_back(Vertex(p2, n4, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), t3));
    vertices.push_back(Vertex(p1, n4, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), t0));

    return vertices;
}

std::vector<Vertex> rotateCube(std::vector<Vertex> vertices, float angleX, float angleY, float angleZ) {
    // Create a 4x4 identity matrix
// Define rotation angles


    // Define rotation axis vectors
    glm::vec3 axisX = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 axisY = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 axisZ = glm::vec3(0.0f, 0.0f, 1.0f);

    // Create rotation matrices
    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(angleX), axisX);
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(angleY), axisY);
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(angleZ), axisZ);

    glm::mat4 rotationMatrix = rotationX * rotationY * rotationZ;
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].position = glm::vec3(rotationMatrix * glm::vec4(vertices[i].position, 1.0f));
    }
    return vertices;
}
