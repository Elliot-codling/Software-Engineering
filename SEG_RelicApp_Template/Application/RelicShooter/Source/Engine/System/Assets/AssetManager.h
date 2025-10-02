#ifndef _TEXTURE_MANAGER_H
#define _TEXTURE_MANAGER_H

#include <map>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

constexpr int DEFAULT_TEXTURE_WIDTH = 16;
constexpr int DEFAULT_TEXTURE_HEIGHT = 16;

constexpr unsigned NUM_SAMPLES = 44100;

class AssetManager
{
public:

	AssetManager();
	~AssetManager();

	sf::Texture& GetTexture(const char* filename);
	bool LoadTextureFromFile(const char* filename);

	//Audio: WAV, OGG/Vorbis and FLAC only supported
	sf::SoundBuffer& GetSoundBuffer(const char* filename);
	bool LoadSoundBufferFromFile(const char* filename);

	sf::Font* GetFont(const char* filename);
	bool LoadFontFromFile(const char* filename);
	
private:

	void InitialiseDefaultTexture();
	void InitialiseDefaultSoundBuffer();
	
	sf::Texture m_DefaultTexture;
	sf::Uint8 m_DefaultTexturePixels[DEFAULT_TEXTURE_WIDTH * DEFAULT_TEXTURE_HEIGHT * 4]{}; //*4 for rgba per pixel

	sf::SoundBuffer m_DefaultSoundBuffer;
	sf::Int16 defaultSoundBufferSamples[NUM_SAMPLES]{};

	std::map<unsigned int, sf::Texture> m_Textures;

	std::map<unsigned int, sf::SoundBuffer> m_SoundBuffers;

	std::map<unsigned int, sf::Font> m_Fonts;

};

#endif
