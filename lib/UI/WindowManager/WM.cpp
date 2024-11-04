#include "WM.h"

WM::WM() {
    // Initialize the window manager
    std::cout << "Initializing window manager" << std::endl;
    // const GLubyte* version = glGetString(GL_VERSION);
    // if(!version) {
    //     std::cerr << "Failed to get OpenGL version" << std::endl;
    //     return;
    // }
    // std::cout << "OpenGL Version: " << version << std::endl;
}

WM::~WM() {
    // Destroy the window manager
    Cleanup();
    std::cout << "Destroying window manager" << std::endl;
}

void WM::Cleanup() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
    m_window = nullptr;
    m_size = {0, 0};
    m_title = nullptr;
    delete m_renderer;
    m_renderer = nullptr;
    std::cout << "Cleaned up window manager" << std::endl;
}

void WM::CreateWindow(int Width, int Height, const char* Title) {
    std::cout << "Creating window" << std::endl;
    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }
    m_size = {Width, Height};
    m_title = Title;
    // Create a window
    m_window = glfwCreateWindow(Width, Height, Title, nullptr, nullptr);
    if(!m_window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    if(glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return;
    }

    m_renderer = new Render(m_window);
    try{
        m_renderer->Init(
            {V_SHADER, F_SHADER},
            m_size
        );
    } catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
        return;
    }

    std::cout << "Creating window with width " << Width << ", height " << Height << ", and title " << Title << std::endl;
}

void WM::Show() {
    // Show the window
    if(!m_window) {
        std::cerr << "Window not created" << std::endl;
        return;
    }

    while(!glfwWindowShouldClose(m_window)) {
        m_elements.clear();
        m_elements = m_renderer->GetElements();
        // std::cout << "Elements size: " << m_elements.size() << std::endl;
        glClear(GL_COLOR_BUFFER_BIT);
        m_renderer->RenderFrame();
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    Cleanup();
}