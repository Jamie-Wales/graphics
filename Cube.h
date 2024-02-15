//
// Created by jamielinux on 2/13/24.
//

#ifndef SVCUBE_CUBE_H
#define SVCUBE_CUBE_H

#include "Shader.h"
#include <vector>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Cube {
    public:
    unsigned int VAO, VBO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices; // Corrected spelling

    Cube(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Cube();
    void draw(glm::mat4 viewMatrix, glm::mat4 proectionMatrix, Shader &shader);

    void draw(glm::mat4 projectionMatrix, Shader &shader, std::vector<glm::vec3> positions);
};

#endif //SVCUBE_CUBE_H
