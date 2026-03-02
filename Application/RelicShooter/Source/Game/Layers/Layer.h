#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <SFML/System/Vector2.hpp>

class GameObject;
class TileMap;

class BaseLayer {
public:
    BaseLayer() = default;
    virtual ~BaseLayer() = default;

public:
    virtual void Initialise();
    virtual void Update(float deltaTime);

    virtual void AddDrawablesToRender();
    virtual void AddGameObjectsToRender(std::vector<GameObject*> renderQueue);

	void ShouldUpdateTick(bool val) { m_shouldLayerUpdate = val; }

protected:
    bool m_shouldLayerUpdate = true;
};


class EnvironmentLayer : public BaseLayer {
public:
    EnvironmentLayer() = default;
    ~EnvironmentLayer() override {
        /* Object clean-up */
        //for (const auto& object : m_objects) {
        //    C_SysContext::Get<RenderManager>()->RemoveRenderObject(object);
        //}
    }

public:
    void Initialise() override;
    void Update(float deltaTime) override;

    void AddDrawable(TileMap& drawable) {
        m_objects.emplace_back(&drawable);
    };

    void AddDrawablesToRender() override;
    void AddGameObjectsToRender(std::vector<GameObject*> renderQueue) override;
private:
    std::vector<TileMap*> m_objects;
};


class UILayer : public BaseLayer {
public:
    UILayer() = default;
    ~UILayer() override = default;

public:
    void Initialise() override;
    void Update(float deltaTime) override;

private:
    sf::Vector2f m_mousePos;
};


class DebugLayer : public BaseLayer {
public:
    DebugLayer() = default;
    ~DebugLayer() override = default;

public:
    void Initialise() override;
    void Update(float deltaTime) override;
};

#endif