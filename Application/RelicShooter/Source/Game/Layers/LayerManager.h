#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <map>
#include <string>
#include <memory>

#include "Layer.h"


class LayerManager {
public:
    LayerManager() = default;
    ~LayerManager() { m_layerStack.clear(); }

    void PushLayer(const char* layerName, std::unique_ptr<BaseLayer> layer);
    void PushLayersToRender();

public:
    std::map<const char*, std::unique_ptr<BaseLayer>> m_layerStack;
};

#endif