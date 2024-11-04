#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include <Renderer/Renderer.h>


class WM {
    public:
        WM();
        ~WM();
        WM& operator=(const WM& other) {
            std::cout << "Copying window manager" << std::endl;
            if(this != &other) {
                m_window = other.m_window;
                m_size = other.m_size;
                m_title = other.m_title;
            }
            return *this;
        }

        void CreateWindow(int Width, int Height, const char* Title);
        void Show();

    private:
        void Cleanup();

    private:
        GLFWwindow* m_window;
        Render* m_renderer = nullptr;
        std::array<int, 2> m_size;
        const char* m_title;
        std::vector<Mesh*> m_elements;
        

    public:
        inline int GetWidth() { return m_size[0]; }
        inline int GetHeight() { return m_size[1]; }
        inline const char* GetTitle() { return m_title; }
        inline GLFWwindow* GetWindow() { return m_window; }
        inline Render* GetRenderer() { return m_renderer; }
};