#pragma once
#ifndef ModelManager_hpp
#define ModelManager_hpp
#include <iostream>
#include <Renderer/Types.hpp>
#include <Renderer/Model/ModelInterface.hpp>
#include <Renderer/Model/Rect.hpp>
#include <vector>
#endif

namespace Model {
    class ModelManager {
        public:
            std::vector<ModelInterface*> m_models;
        public:
            ModelManager() {
                std::cout << "Instantiating ModelManager" << std::endl;
            }

            ~ModelManager() {
                std::cout << "Destroying ModelManager" << std::endl;
                for(auto& model : m_models) {
                    delete model;
                }
                m_models.clear();
            }

            void Create(int type, float width, float height);
    };
}