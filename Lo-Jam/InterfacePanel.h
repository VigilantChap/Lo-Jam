#ifndef INTERFACE_PANEL_H
#define INTERFACE_PANEL_H

#include "Interface.h"
#include "InterfaceText.h"

class InterfacePanel : public Interface
{
public:
	InterfacePanel(std::string pText, float pWidth, float pHeight, float pX = 0, float pY = 0, Anchor pAnchor = Anchor::MID_CENTER, Anchor pTextAnchor = Anchor::MID_CENTER);
	~InterfacePanel();

	void Draw(sf::RenderWindow* pWindow, sf::View pCamView, sf::FloatRect* pParentRect = nullptr) override;

	void SetText(std::string pText);
	void SetFontSize(uint pFontSize);
	void SetTextColor(sf::Color pColor);

protected:
	InterfaceText* panelText;

	sf::RectangleShape background;
	sf::Color backgroundColor;
	int padding; //spacing between a container and its contents
};

#endif // INTERFACE_PANEL_H