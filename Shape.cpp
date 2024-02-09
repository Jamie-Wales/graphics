//
// Created by jamielinux on 2/9/24.
//

#include <stdexcept>
#include "Shape.h"
unsigned int Shape::vao = 0;
bool Shape::initialised = false;

Shape::Shape(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
        : vertices(vertices), indices(indices) {
    VBO = 0;
    EBO = 0;
    if (!initialised) {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        initialised = true;
    }

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);



    if (VBO ==0 || EBO ==0) {
        throw std::runtime_error("Cannot init VBO or EBO");
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void Shape::draw() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Shape::draw(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix, Shader &shader) {  
    glUseProgram(shader.handle());
    glUniformMatrix4fv(glGetUniformLocation(shader.handle(), "ProjectionMatrix"), 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader.handle(), "ModelViewMatrix"), 1, GL_FALSE, &modelViewMatrix[0][0]);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Shape::~Shape() {
    // Delete the VBO, EBO, and VAO
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
