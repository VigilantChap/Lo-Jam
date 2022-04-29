#ifndef INTERFACE_PANEL_H
#define INTERFACE_PANEL_H

#include "SFML.h"

class InterfacePanel : public sf::Sprite
{
public:
	enum Anchor
	{
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		MID_LEFT,
		MID_CENTER,
		MID_RIGHT,
		BOT_LEFT,
		BOT_CENTER,
		BOT_RIGHT
	};

	InterfacePanel(std::string pText, float pWidth, float pHeight, float pX = 0, float pY = 0, Anchor pAnchor = Anchor::MID_CENTER);
	~InterfacePanel();

	virtual void SetText(std::string& pText);
	virtual void Draw(sf::RenderWindow* pWindow, sf::View pCamView);

	void SetFontSize(uint pFontSize);
	void SetAnchor(Anchor pAnchor);

protected:
	Anchor anchor;
	//sf::Vector2f position;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text text;
	sf::Color fillColor;
	sf::Text::Style fontStyle;
	uint fontSize;
	int hPadding; //horizontal spacing between a container and its contents
	float scaleX;
	float scaleY;
	std::string plainText;
};

#endif // INTERFACE_PANEL_H