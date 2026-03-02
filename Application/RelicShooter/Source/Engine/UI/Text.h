#ifndef _TEXT_H
#define _TEXT_H

#include "SFML\Graphics.hpp"

class Text : public sf::Text
{
public:

	Text();
	~Text();

	void Initialise(const char* filename, const char* text,sf::Color pcolour, int psize, bool isUIObject = false);

private:
	bool m_Initialised;

};

#endif
