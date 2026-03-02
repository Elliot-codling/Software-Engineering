#pragma once
class EnemyWave
{
public:
	//-------CONSTRUCTORS/DESTRUCTORS-------------------------------------------
	EnemyWave();
	~EnemyWave();

	//-------FUNCTIONS----------------------------------------------------------
public:
	int* LoadEnemyWaveFromFile(const char* waveName);
	size_t GetAmountOfTiles() const { return m_mapWidth * m_mapHeight; }

	//-------MEMBER DATA----------------------------------------------------------
private:
	// Map
	const size_t m_mapWidth = 60;
	const size_t m_mapHeight = 35;
};

