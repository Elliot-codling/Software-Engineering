#ifndef _GAME_DATA_MANAGER_H
#define _GAME_DATA_MANAGER_H

#include <map>

struct SpritesheetDef;

class GameDataManager
{
public:
	GameDataManager();
	~GameDataManager();

	static void Initialise();

	void AddSpritesheetDef(const char* filename, SpritesheetDef* pSpritesheetDef);
	SpritesheetDef* GetSpritesheetDef(const char* filename);

	bool LoadSpritesheetDefFromFile(const char* filename);

private:

	std::map<int, SpritesheetDef*> m_SpritesheetDefs;

};

#endif
