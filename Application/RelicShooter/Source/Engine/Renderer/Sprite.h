#ifndef _SPRITE_H
#define _SPRITE_H

#include <SFML/Graphics.hpp>

class TextureManager;

class Sprite : public sf::Sprite
{
public: 
	Sprite();
	~Sprite() override;

	void Initialise(const char* filename,sf::Color pcolour,float pscale, bool isUIObject = false);

	void SetTexture(const char* fileName, const bool repeat = false);
	void AddToRenderQueue();
private:
	bool m_isUIObject = false;
	bool m_bInitialised;
};

#endif
