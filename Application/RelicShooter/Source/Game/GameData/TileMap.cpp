#include "TileMap.h"

#include "../DebugHandler.hpp"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Renderer/RenderManager.h"
#include "GameDataManager.h"
#include "../../Engine/System/Assets/AssetManager.h"
#include "SpritesheetDef.h"
#include <fstream>


TileMap::TileMap()
{

}

TileMap::~TileMap()
{
	C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);
}

void TileMap::Initialise()
{
	
}

void TileMap::Update()
{
	
}

bool TileMap::LoadSpriteFromSpritesheetDef(SpritesheetDef* pSpritesheetDef, const int* tiles, const char* layerName)
{
	if (!pSpritesheetDef)
			return false;

	std::vector<sf::IntRect> frames = GetTileSet(pSpritesheetDef);
	const size_t numTiles = CalculateNumberOfTiles(tiles, frames.size());

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(numTiles * 4);

	int quadNum = 0;
	for (size_t xAxis = 0; xAxis < m_mapWidth; ++xAxis)
	{
		for (size_t yAxis = 0; yAxis < m_mapHeight; ++yAxis)
		{
			// get the current tile number
			const size_t tileNo = tiles[xAxis + (yAxis * m_mapWidth)];
			//If the tile number is outside the range of valid tiles, leave it blank
			if (tileNo < 0 || tileNo >= frames.size())
				continue;

			const int tu1 = frames[tileNo].left;
			const int tv1 = frames[tileNo].top;
			const int tu2 = tu1 + frames[tileNo].width;
			const int tv2 = tv1 + frames[tileNo].height;
			const int tstartvertindex = quadNum * 4;
			sf::Vertex* quad = &m_vertices[tstartvertindex];

			// define its 4 corners (Geometric Position)
			quad[0].position = sf::Vector2f(sf::Vector2i(xAxis * frames[tileNo].width, yAxis * frames[tileNo].height));
			quad[1].position = sf::Vector2f(sf::Vector2i((xAxis + 1) * frames[tileNo].width, yAxis * frames[tileNo].height));
			quad[2].position = sf::Vector2f(sf::Vector2i((xAxis + 1) * frames[tileNo].width,(yAxis + 1) * frames[tileNo].height));
			quad[3].position = sf::Vector2f(sf::Vector2i(xAxis * frames[tileNo].width, (yAxis + 1) * frames[tileNo].height));

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(sf::Vector2i(tu1, tv1));
			quad[1].texCoords = sf::Vector2f(sf::Vector2i(tu2, tv1));
			quad[2].texCoords = sf::Vector2f(sf::Vector2i(tu2, tv2));
			quad[3].texCoords = sf::Vector2f(sf::Vector2i(tu1, tv2));
			//Add to the Total number of Tiles
			quadNum++;
		}
	}

	//Add this Game Object to the RenderManager (object is sub class of sf::Drawable).
	if (FindLayerName(layerName, "bulletcollision") == false)
		C_SysContext::Get<RenderManager>()->AddRenderObject(this);
	//If we've reached here, then we have a valid tilemap.
	return true;
}

void TileMap::LoadFromFile(const char* layerName, const char* spritesheetName)
{
	auto* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSSDef = pGameDataManager->GetSpritesheetDef(spritesheetName);

	const bool collisionlayerfound = FindLayerName(layerName, "collision");
	
	// Read the file and store the value into our map
	std::ifstream file{};
	file.open(layerName);

	if (!file.is_open())
	{
		char message[1024];
		strerror_s(message, 1024, errno);
		LOG("Error: " + std::string(message));
		return;
	}

	// Create new tile
	int* pMap = new int[m_mapWidth * m_mapHeight];
	int tileinput;
	for (size_t i = 0; i < m_mapWidth * m_mapHeight; i++)
	{
		file >> tileinput;
		pMap[i] = tileinput - 1;
	}
	file.close();

	LoadSpriteFromSpritesheetDef(pSSDef, pMap, layerName);
	if (collisionlayerfound)
	{
		AddCollisions();
	}
	delete[] pMap;

}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//apply the transform (to position the tile map)
	states.transform *= getTransform();

	//apply the tile set texture (to the shader)
	states.texture = m_pTileSet;

	//draw the vertex array
	target.draw(m_vertices, states);
}

bool TileMap::FindLayerName(const char* name, const char* find)
{
	std::string testString = name;
	size_t index = testString.find(find);
	if (index != std::string::npos)
	{
		return true;
	}
	return false;
}


size_t TileMap::CalculateNumberOfTiles(const int* tiles, size_t numberOfFrames)
{
	size_t numOfTiles = 0;
	for (size_t index = 0; index < m_mapWidth * m_mapHeight; index++)
	{
		const size_t tileNumber = tiles[index];
		if (tileNumber < 0 || tileNumber >= numberOfFrames)
		{
			continue;
		}
		numOfTiles++;
	}
	return numOfTiles;
}

std::vector<sf::IntRect> TileMap::GetTileSet(SpritesheetDef* spriteSheet)
{
	// Load the tileset
	AssetManager* assetManager = C_SysContext::Get<AssetManager>();
	m_pTileSet = &assetManager->GetTexture(spriteSheet->m_Filename.c_str());

	// Add each tile frame
	std::vector<sf::IntRect> frames;
	for (SpritesheetSpriteDef& m_pSpriteDef : spriteSheet->m_pSpriteDefs)
	{
		const sf::IntRect rect(
			m_pSpriteDef.m_PosX,
			m_pSpriteDef.m_PosY, 
			m_pSpriteDef.m_Width, 
			m_pSpriteDef.m_Height
		);

		frames.emplace_back(rect);
	}

	return frames;
}

//Returns the tile the object is located in
size_t TileMap::TileIndexAtPosition(const sf::Vector2f pos)
{
	const size_t xAxis = static_cast<int>(floor(pos.x / static_cast<float>(m_tileWidth)));
	const size_t yAxis = static_cast<int>(floor(pos.y / static_cast<float>(m_tileHeight)));

	return xAxis + (yAxis * m_mapWidth);
}

void TileMap::AddCollisions()
{
	size_t count = 0;
	for (size_t index = 0; index < m_vertices.getVertexCount(); index += 4)
	{
		count++;
		const sf::Vector2f position = m_vertices[index].position;
		const size_t tileIndex = TileIndexAtPosition(position);
		const sf::FloatRect rect(position.x, position.y, m_tileWidth, m_tileHeight);
		m_collisionLayer[tileIndex] = BoxCollider2D{ rect };
	}
}

std::map<size_t, BoxCollider2D>& TileMap::GetWorldCollisions()
{
	return m_collisionLayer;
}



