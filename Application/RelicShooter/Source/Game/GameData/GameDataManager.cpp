#include "GameDataManager.h"
#include "../../Engine/Core/Types.h"
#include "SpritesheetDef.h"

#include <tinyxml2.h>

#include "../DebugHandler.hpp"
GameDataManager::GameDataManager()
{

}

GameDataManager::~GameDataManager()
{

}

void GameDataManager::Initialise()
{

}

void GameDataManager::AddSpritesheetDef(const char* filename, SpritesheetDef* pSpritesheetDef)
{
	C_Hash32 filenameHash(filename);

	if (m_SpritesheetDefs.find(filenameHash.GetHashValue()) != m_SpritesheetDefs.end())
		return;

	m_SpritesheetDefs[filenameHash.GetHashValue()] = pSpritesheetDef;
}

SpritesheetDef* GameDataManager::GetSpritesheetDef(const char* filename)
{
	C_Hash32 filenameHash(filename);

	std::map<int, SpritesheetDef*>::iterator iter = m_SpritesheetDefs.find(filenameHash.GetHashValue());
	
	if (iter != m_SpritesheetDefs.end())
		return iter->second;

	if (LoadSpritesheetDefFromFile(filename))
	{
		return GetSpritesheetDef(filename);
	}

	return nullptr;
}

bool GameDataManager::LoadSpritesheetDefFromFile(const char* filename)
{
	tinyxml2::XMLDocument doc;

	if (doc.LoadFile(filename) != tinyxml2::XMLError::XML_SUCCESS)
		return false;

	tinyxml2::XMLElement* pTextureAtlas = doc.FirstChildElement("TextureAtlas");

	if (pTextureAtlas)
	{
		SpritesheetDef* pSpritesheetDef = new SpritesheetDef();

		//extract attributes from TextureAtlas
		for (const tinyxml2::XMLAttribute* attribute = pTextureAtlas->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			if (strcmp(attribute->Name(), "imagePath") == 0)
			{
				const std::string path = FindDirectory(filename);
				pSpritesheetDef->m_Filename = path + attribute->Value();
			}
			else if (strcmp(attribute->Name(), "width") == 0)
			{
				pSpritesheetDef->m_Width = attribute->IntValue();
			}
			else if (strcmp(attribute->Name(), "height") == 0)
			{
				pSpritesheetDef->m_Height = attribute->IntValue();
			}
		}

		//loop through sprites
		for (tinyxml2::XMLNode* ele = pTextureAtlas->FirstChild(); ele; ele = ele->NextSibling())
		{
			SpritesheetSpriteDef spritesheetSpriteDef;

			//extract attributes from sprite
			for (const tinyxml2::XMLAttribute* attribute = ((tinyxml2::XMLElement*)ele)->FirstAttribute(); attribute; attribute = attribute->Next())
			{
				if(strcmp(attribute->Name(), "n") == 0)
				{
					spritesheetSpriteDef.m_Name = attribute->Value();
				}
				else if (strcmp(attribute->Name(), "x") == 0)
				{
					spritesheetSpriteDef.m_PosX = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "y") == 0)
				{
					spritesheetSpriteDef.m_PosY = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "w") == 0)
				{
					spritesheetSpriteDef.m_Width = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "h") == 0)
				{
					spritesheetSpriteDef.m_Height = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "pX") == 0)
				{
					spritesheetSpriteDef.m_PivotX = attribute->FloatValue();
				}
				else if (strcmp(attribute->Name(), "pY") == 0)
				{
					spritesheetSpriteDef.m_PivotY = attribute->FloatValue();
				}
				else if (strcmp(attribute->Name(), "oX") == 0)
				{
					spritesheetSpriteDef.m_OffsetX = (float)attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "oY") == 0)
				{
					spritesheetSpriteDef.m_OffsetY = (float)attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "oW") == 0)
				{
					spritesheetSpriteDef.m_OriginalWidth = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "oH") == 0)
				{
					spritesheetSpriteDef.m_OriginalHeight = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "r") == 0)
				{
					spritesheetSpriteDef.m_Rotated = true;
				}					
			}

			pSpritesheetDef->m_pSpriteDefs.emplace_back(spritesheetSpriteDef);
		}

		AddSpritesheetDef(filename, pSpritesheetDef);

		return true;

	}

	return false;
}

std::string GameDataManager::FindDirectory(const char* string)
{
	const std::string buffer = std::string(string);
	const size_t index = buffer.rfind('/');

	return buffer.substr(0, index + 1);
}
