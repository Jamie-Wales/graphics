#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Square.h"
#include "Cube.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);
int height = 800;
int width = 800;
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 ModelViewMatrix = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(40.0f), (float)width/(float)height, 0.1f, 200.0f);
float Angle = 5.00f;

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow *window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (glewInit()) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader;
    shader.load("basic", "../basicTransformations.vert", "../basicTransformations.frag");
    float dim = 0.25f;
    std::vector<float> verts{
        //Vertex
        -dim, -dim, -dim, 0.0, 0.0, 0.0, 1.0f, 1.0f,
        -dim, dim, -dim, 0.0, 1.0, 0.0, 1.0f, 0.0f,
        dim, dim, -dim, 0.0, 0.0, 1.0, 0.0f, 0.0f,
        dim, -dim, -dim, 1.0, 1.0, 1.0, 1.0f, 1.0f,
        -dim, -dim, dim, 1.0, 0.0, 0.0, 1.0f, 0.0f,
        -dim, dim, dim, 0.0, 1.0, 0.0, 0.0f, 0.0f,
        dim, dim, dim, 0.0, 0.0, 1.0, 1.0f, 1.0f,
        dim, -dim, dim, 1.0, 1.0, 0.0, 0.0f, 0.0f};


    std::vector<unsigned int> indicies = {0, 1, 2,
                                          0, 2, 3,
                                          4, 6, 5,
                                          4, 7, 6,
                                          1, 5, 6,
                                          1, 6, 2,
                                          0, 7, 4,
                                          0, 3, 7,
                                          0, 5, 1,
                                          0, 4, 5,
                                          3, 2, 7,
                                          2, 6, 7};


    Cube cube {verts, indicies};
    glEnable(GL_DEPTH_TEST);
    std::vector<glm::vec3> cubePositions = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cube.draw(ProjectionMatrix, shader, cubePositions);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }


    glfwTerminate();
    return 0;
}

// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    ProjectionMatrix = glm::perspective(glm::radians(40.0f), (float)width/(float)height, 0.1f, 200.0f);

}
