#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include "ModelInterface.hpp"

namespace Model {
    class Rect : public ModelInterface {
        public:
            float width, height;
            Mesh* m_mesh = nullptr;
        public:
            Rect(float width, float height): width(width), height(height) {
                std::cout << "Instantiating Rect" << std::endl;
                std::vector<Vertex> vertices = {
                    Vertex(glm::vec3(0.0f, 0.0f, 0.0f)),
                    Vertex(glm::vec3(width, 0.0f, 0.0f)),
                    Vertex(glm::vec3(width, height, 0.0f)),
                    Vertex(glm::vec3(0.0f, height, 0.0f))
                };
                std::vector<unsigned int> indices = {
                    0, 1, 2,
                    2, 3, 0
                };
                m_mesh = new Mesh(vertices, indices);
            }

            ~Rect() {
                std::cout << "Destroying Rect" << std::endl;
            }
    };
}