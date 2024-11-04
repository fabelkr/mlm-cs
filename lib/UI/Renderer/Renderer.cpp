#include "Renderer.h"

Render::~Render() {
    Cleanup();
    std::cout << "Destroying renderer" << std::endl;
}

const char* Render::loadShader(const char* path)  {
    std::cout << "Loading shader: " << path << std::endl;
    FILE* file = fopen(path, "r");
    if(!file) {
        std::cout << "Failed to open file: " << path << std::endl;
        return nullptr;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer;
    buffer = new char[length + 1];
    fread(buffer, 1, length, file);
    buffer[length + 1] = '\0';
    fclose(file);
    return buffer;
}
    

void Render::Cleanup() {
    glDeleteProgram(m_shaderProgram);
    for(auto& vao : m_VAOs) {
        glDeleteVertexArrays(1, &vao);
        vao = 0u;
    }
    for(auto& vbo : m_VBOs) {
        glDeleteBuffers(1, &vbo);
        vbo = 0u;
    }
    for(auto& ebo : m_EBOs) {
        glDeleteBuffers(1, &ebo);
        ebo = 0u;
    }
    m_shaderProgram = 0u;

    std::cout << "Cleaned up renderer" << std::endl;
}

// 1st shader is vertex shader, 2nd shader is fragment shader
void Render::CompileShaders(std::array<const char*, 2> shaders) {
    for(auto& shader : shaders) {
        shader = loadShader(shader);
    }

    std::cout << "Compiling shaders" << std::endl;

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &shaders[0], nullptr);
    glCompileShader(vertexShader);

    std::cout << "Vertex shader compiled" << std::endl;

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &shaders[1], nullptr);
    glCompileShader(fragmentShader);

    std::cout << "Fragment shader compiled" << std::endl;

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    std::cout << "Shader program linked" << std::endl;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    auto glVersion = glGetString(GL_VERSION);
    if(!glVersion) {
        std::cerr << "Failed to get OpenGL version" << std::endl;
        return;
    }
    std::cout << "OpenGL Version: " << glVersion << std::endl;

}

void Render::CreateBuffers() {
    for(auto& el : m_elements) {
        GLuint VAO, VBO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, el->vertices.size() * sizeof(Vertex), el->vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, el->indices.size() * sizeof(unsigned int), el->indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
        m_VAOs.push_back(VAO);
        m_VBOs.push_back(VBO);
        m_EBOs.push_back(EBO);
    }
}

void Render::SetupOrthographicProjection(std::array<int, 2>& size) {
    m_projection = glm::ortho(0.0f, static_cast<float>(size[0]), 0.0f, static_cast<float>(size[1]));
}

void Render::RenderFrame() {
    if(m_elements.empty()) {return;}
    Render::CreateBuffers();
    std::cout << "Rendering frame" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);
    for (size_t i = 0; i < m_elements.size(); ++i) {
        glUseProgram(m_shaderProgram);

        glBindVertexArray(m_VAOs[i]);
        glDrawElements(GL_TRIANGLES, m_elements[i]->indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

void Render::CreateElement(int type, float width, float height) {
    m_modelManager->Create(type, width, height);
    std::cout << "Creating element" << std::endl;
}

std::vector<Model::ModelInterface*> Render::GetModels() {
    return m_modelManager->m_models;
}

std::vector<Mesh*> Render::GetElements() {
    // std::cout << "Getting elements" << std::endl;
    std::cout << "elements size: " << m_modelManager->m_models.size() << std::endl;
    std::vector<Mesh*> elements;
    elements.reserve(m_modelManager->m_models.size());
    for(auto& model : m_modelManager->m_models) {
        elements.emplace_back(model->m_mesh);
    }
    // m_elements.clear();
    m_elements = elements;
    return elements;
}