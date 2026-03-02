#include "Layer.h"

void BaseLayer::Initialise() {
}

void BaseLayer::Update(float deltaTime) {
}

void BaseLayer::AddDrawablesToRender() {
}

void BaseLayer::AddGameObjectsToRender(std::vector<GameObject*> renderQueue) {
}

void EnvironmentLayer::Initialise() {
    BaseLayer::Initialise();
}

void EnvironmentLayer::Update(float deltaTime) {
    BaseLayer::Update(deltaTime);
}

void EnvironmentLayer::AddDrawablesToRender() {
    /* Add each object to render queue, they get removed and deleted on destructor call */
    //for (const auto& tilemap : m_objects) {
        //C_SysContext::Get<RenderManager>()->AddRenderObject(tilemap);
    //}
}

void EnvironmentLayer::AddGameObjectsToRender(std::vector<GameObject*> renderQueue) {
    BaseLayer::AddGameObjectsToRender(renderQueue);
}

