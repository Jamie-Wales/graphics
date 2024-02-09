#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Shape.h"




void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix = glm::ortho(-5.0, 5.0, -5.0, 5.0);
float Angle = 0.0f;

int main() {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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
    std::vector<float> vertices = {
            0.25f,  0.25f,  0.0f, 1.0f, 0.0f, 0.0f, // Top Right
            0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
            -0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom Left
            -0.25f,  0.25f, 0.0f, 1.0f, 1.0f, 0.0f, // Top Left
    };
  std::vector<unsigned int> indices = {
      // note that we start from 0!
      0, 1, 3, // first Triangle
      1, 2, 3  // second Triangle
  };


  std::vector<float> vertices2 = {
          -0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, // Top Right
          -0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
          0.25f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom Left

  };

    std::vector<unsigned int> indices2 = {
            // note that we start from 0!
            0, 1, 3, // first Triangle
    };

  Shape one = {vertices, indices};
  Shape two = {vertices2, indices2};

  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));
    glm::mat4 ModelViewMatrix = glm::rotate(ViewMatrix, Angle, glm::vec3(10, 0.0, 1.0));
    one.draw(ProjectionMatrix, ModelViewMatrix, shader);
    ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(1.0, 3.0, 0.0));
    two.draw(ProjectionMatrix, ModelViewMatrix, shader);
    glfwSwapBuffers(window);
    glfwPollEvents();

    Angle += 0.05;
    if (Angle >= 2.0*3.14159265) {
        Angle = 0;
    }
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
  ProjectionMatrix = glm::ortho(-5.0, 5.0, -5.0, 5.0);
}
