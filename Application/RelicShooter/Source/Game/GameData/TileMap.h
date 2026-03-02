#pragma once

#include "../GameObjects/BaseGameObjects/GameObjectWithSprite.h"

class BoxCollider2D;
struct SpritesheetDef;

class TileMap :public GameObjectWithSprite, sf::Drawable, sf::Transformable
{
public:
	//-------CONSTRUCTORS/DESTRUCTORS-------------------------------------------
	TileMap();
	~TileMap();

	//-------FUNCTIONS----------------------------------------------------------
public:
	void Initialise() override;
	void Update() override;


	bool LoadSpriteFromSpritesheetDef(SpritesheetDef* pSpritesheetDef, const int* tiles, const char* layerName);
	void LoadFromFile(const char* layerName, const char* spritesheetName);

	// --- Collisions ---
	size_t TileIndexAtPosition(sf::Vector2f pos);
	void AddCollisions();
	std::map<size_t, BoxCollider2D>& GetWorldCollisions();

	
protected:
	// SFML render override
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	bool FindLayerName(const char* name, const char* find);
	size_t CalculateNumberOfTiles(const int* tiles, size_t numberOfFrames);
	std::vector<sf::IntRect> GetTileSet(SpritesheetDef* spriteSheet);

private:
	//-------MEMBER DATA----------------------------------------------------------
	sf::VertexArray m_vertices;
	sf::Texture* m_pTileSet;

	std::map<size_t, BoxCollider2D> m_collisionLayer;

	// Map
	const size_t m_mapWidth = 60;
	const size_t m_mapHeight = 35;

	// Tiles
	const size_t m_tileWidth = 64;
	const size_t m_tileHeight = 64;
};

