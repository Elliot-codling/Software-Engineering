#ifndef _TEXT_H
#define _TEXT_H

#include "SFML/Graphics.hpp"

class Text : public sf::Text
{
public:

	Text();
	~Text() override;

	void Initialise(const char* filename, const char* text);

private:
	bool m_Initialised;

};

#endif
