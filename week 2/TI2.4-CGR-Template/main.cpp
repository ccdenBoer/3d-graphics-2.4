#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

void init();
void update();
void draw();
std::vector<Vertex> createCube();

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
    });

}


void update()
{

}

void draw()
{
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 100.0f);

    tigl::shader->setProjectionMatrix(projection);
    tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(1, 1, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
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

    static std::vector<Vertex> vertices = createCube();

    tigl::drawVertices(GL_QUADS, vertices);

}

// Function to create a cube using a vector of vertices
std::vector<Vertex> createCube()
{
    std::vector<Vertex> vertices;

    // Vertex positions
    glm::vec3 p0(-0.5f, -0.5f, 0.5f); // front bottom left
    glm::vec3 p1(0.5f, -0.5f, 0.5f); // front bottom right
    glm::vec3 p2(0.5f, 0.5f, 0.5f); // front top right
    glm::vec3 p3(-0.5f, 0.5f, 0.5f); // front top left
    glm::vec3 p4(-0.5f, -0.5f, -0.5f); // back bottom left
    glm::vec3 p5(0.5f, -0.5f, -0.5f); // back bottom right
    glm::vec3 p6(0.5f, 0.5f, -0.5f); // back top right
    glm::vec3 p7(-0.5f, 0.5f, -0.5f); // back top left

    // Vertex normals
    glm::vec3 n0(0.0f, 0.0f, 1.0f); // front
    glm::vec3 n1(1.0f, 0.0f, 0.0f); // right
    glm::vec3 n2(0.0f, 0.0f, -1.0f); // back
    glm::vec3 n3(-1.0f, 0.0f, 0.0f); // left
    glm::vec3 n4(0.0f, 1.0f, 0.0f); // top
    glm::vec3 n5(0.0f, -1.0f, 0.0f); // bottom

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
    vertices.push_back(Vertex(p4, n4, glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), t0));
    vertices.push_back(Vertex(p5, n4, glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), t1));
    vertices.push_back(Vertex(p1, n4, glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), t2));
       
    return vertices;
}
