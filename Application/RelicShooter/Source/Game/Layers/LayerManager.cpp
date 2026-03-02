#include "LayerManager.h"

#include "../DebugHandler.hpp"

void LayerManager::PushLayer(const char* layerName, std::unique_ptr<BaseLayer> layer) {
    std::string output = "Layer '" + std::string(layerName) + "' added"; LOG(output)
    m_layerStack.emplace(layerName, std::move(layer));
}

/* Use to push all current layers to the renderer */
void LayerManager::PushLayersToRender() {
    /* Only add drawables for now */
    for (auto& pair : m_layerStack) {
        pair.second->AddDrawablesToRender();
    }
}