#pragma once
#ifndef CLR_WHITE
    #include <iostream>
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
    #include <glm/glm.hpp>
    #include <vector>

    #define CLR_WHITE glm::vec4(1.0f)
    #define CLR_BLACK glm::vec4(0.0f)
    #define CLR_RED glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
    #define CLR_GREEN glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)
    #define CLR_BLUE glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
    #define CLR_YELLOW glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)
    #define CLR_TRANSPARENT glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)

#endif
struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texCoord;

    Vertex() : position(glm::vec3(0.0f)), color(glm::vec4(1.0f)), texCoord(glm::vec2(0.0f)) {}
    Vertex(const glm::vec3& position, const glm::vec4& color, const glm::vec2& texCoord): position(position), color(color), texCoord(texCoord) {}
    Vertex(const Vertex& other): position(other.position), color(other.color), texCoord(other.texCoord) {}
    Vertex(const glm::vec3& position): position(position), color(glm::vec4(1.0f)), texCoord(glm::vec2(0.0f)) {}
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh() = default;
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices): vertices(vertices), indices(indices) {}
    Mesh(const Mesh& other): vertices(other.vertices), indices(other.indices) {}
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const glm::vec4& color): vertices(vertices), indices(indices) {
        for(auto& vertex : this->vertices) {
            vertex.color = color;
        }
    }
};

enum ModelType {
    RECTANGLE,
    CIRCLE
};