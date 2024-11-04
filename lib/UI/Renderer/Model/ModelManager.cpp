#include "ModelManager.hpp"

namespace Model {
    void ModelManager::Create(int type, float width, float height) {
        switch(type) {
            case ModelType::RECTANGLE:
                m_models.push_back(new Rect(width, height));
                break;
            case ModelType::CIRCLE:
                break;
            default:
                break;
        }
    }
}