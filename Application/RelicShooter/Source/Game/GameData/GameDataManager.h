#ifndef _GAME_DATA_MANAGER_H
#define _GAME_DATA_MANAGER_H

#include <map>
#include <string>

struct SpritesheetDef;

class GameDataManager
{
public:
	GameDataManager();
	~GameDataManager();

	void Initialise();

	void AddSpritesheetDef(const char* filename, SpritesheetDef* pSpritesheetDef);
	SpritesheetDef* GetSpritesheetDef(const char* filename);

	bool LoadSpritesheetDefFromFile(const char* filename);

private:
	std::string FindDirectory(const char* string);
	std::map<int, SpritesheetDef*> m_SpritesheetDefs;

};

#endif
