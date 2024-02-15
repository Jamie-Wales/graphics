//
// Created by jamielinux on 2/13/24.
//

#ifndef SVCUBE_SQUARE_H
#define SVCUBE_SQUARE_H

#include "Shader.h"
#include <vector>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Square {
public:
    unsigned int VAO, VBO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices; // Corrected spelling

    Square(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Square();
    void draw(glm::mat4 viewMatrix, glm::mat4 proectionMatrix, Shader &shader);
};


#endif //SVCUBE_SQUARE_H
