#pragma once
#include <iostream>
#include <Renderer/Types.hpp>

namespace Model {
    class ModelInterface {
        public:
            virtual ~ModelInterface() = default;
            // virtual Mesh* GetModel() = 0;
            
            void SetColor(glm::vec4 color) {
                for(auto& vertex : m_mesh->vertices) {
                    vertex.color = color;
                }
            }

            void SetTexture(glm::vec2 texCoord) {
                for(auto& vertex : m_mesh->vertices) {
                    vertex.texCoord = texCoord;
                }
            }

        public:
            Mesh* m_mesh = nullptr;
            
    };
}