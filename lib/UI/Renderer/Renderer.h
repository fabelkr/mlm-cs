#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>
#include <vector>
#include "Types.hpp"
#include "Model/ModelManager.hpp"

class Render {
    public:
        Render(GLFWwindow* window): m_window(window), m_modelManager(new Model::ModelManager()) {
            std::cout << "Instantiating renderer" << std::endl;
        }
        ~Render();

        void RenderFrame();

    private:
        GLFWwindow* m_window;
        Model::ModelManager* m_modelManager;
        GLuint m_shaderProgram;
        std::vector<GLuint> m_VAOs, m_VBOs, m_EBOs;
        glm::mat4 m_projection;
        std::vector<Mesh*> m_elements;
        void CompileShaders(std::array<const char*, 2> shaders);
        void SetupOrthographicProjection(std::array<int, 2>& size);
        void Cleanup();

        static const char* loadShader(const char* path);
    
    public:
        void CreateBuffers();
        void Init(std::array<const char*, 2> shaders, std::array<int, 2>& size) {
            std::cout << "Initializing renderer" << std::endl;
            CompileShaders(shaders);
            CreateBuffers();
            SetupOrthographicProjection(size);
        }

        void CreateElement(int, float, float); 

        std::vector<Model::ModelInterface*> GetModels();
        std::vector<Mesh*> GetElements();

};