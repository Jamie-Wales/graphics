//
// Created by jamielinux on 2/13/24.
//

#include <stdexcept>
#include "Square.h"

Square::Square(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
        : vertices(vertices), indices(indices) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    if (VAO == 0 || VBO ==0 || EBO ==0) {
        throw std::runtime_error("Cannot init VBO or EBO");
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (indices.size() * 2) * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void Square::draw(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix, Shader &shader) {
    glUseProgram(shader.handle());
    glUniformMatrix4fv(glGetUniformLocation(shader.handle(), "ProjectionMatrix"), 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader.handle(), "ModelViewMatrix"), 1, GL_FALSE, &modelViewMatrix[0][0]);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Square::~Square() {
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
