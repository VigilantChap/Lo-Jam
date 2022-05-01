#ifndef INTERFACE_TEXT_H
#define INTERFACE_TEXT_H

#include "Interface.h"

class InterfaceText : public Interface
{
public:

	InterfaceText(std::string pText, float pX, float pY, float pWidth = 0, float pHeight = 0, Anchor pAnchor = Anchor::MID_CENTER);
	~InterfaceText();

	virtual void SetText(std::string& pText);

	void SetFontSize(uint pFontSize);

	void Draw(sf::RenderWindow* pWindow, sf::View pCamView, sf::FloatRect* pParentRect) override;

protected:
	sf::RectangleShape background;
	sf::Font font;
	sf::Text text;
	sf::Color fontColor;
	sf::Text::Style fontStyle;
	uint fontSize;
	float textWidth;
	float textHeight;
	std::string plainText;
};

#endif // INTERFACE_TEXT_H