#include "EnemyWave.h"
#include "../DebugHandler.hpp"
#include <fstream>

EnemyWave::EnemyWave()
{
}

EnemyWave::~EnemyWave()
{
}

int* EnemyWave::LoadEnemyWaveFromFile(const char* waveName)
{
	std::ifstream file{};
	file.open(waveName);

	if (!file.is_open())
	{
		char message[1024];
		strerror_s(message, 1024, errno);
		LOG("Error: " + std::string(message));
		return nullptr;
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
	return pMap;
}
