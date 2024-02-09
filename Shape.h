//
// Created by jamielinux on 2/9/24.
//

#ifndef SHAPE_H
#define SHAPE_H
#include "Shader.h"
#include <vector>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Shape {
public:
    static unsigned int vao;
    static bool initialised;
    unsigned int VBO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices; // Corrected spelling

    Shape(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Shape();
    void draw();
    void draw(glm::mat4 viewMatrix, glm::mat4 proectionMatrix, Shader &shader);
};

#endif // SHAPE_H


