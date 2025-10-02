#ifndef _SPRITE_H
#define _SPRITE_H

#include <SFML/Graphics.hpp>

class TextureManager;

class Sprite : public sf::Sprite
{
public: 
	Sprite();
	~Sprite() override;

	void Initialise(const char* filename);

private:

	bool m_bInitialised;
};

#endif
