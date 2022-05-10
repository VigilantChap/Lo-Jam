#include "InterfacePanel.h"

#pragma warning (disable: 26812)

InterfacePanel::~InterfacePanel()
{
	delete panelText;
	panelText = nullptr;
}

InterfacePanel::InterfacePanel(std::string pText, float pWidth, float pHeight, float pX, float pY, Anchor pAnchor, Anchor pTextAnchor) :
	backgroundColor(sf::Color::White),
	padding(8),
	Interface(pX, pY, pAnchor)
{
	background.setSize(sf::Vector2f(pWidth, pHeight));
	background.setOrigin(pWidth * scaleWidth, pHeight * scaleHeight);
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(4);
	background.setFillColor(backgroundColor);

	panelText = new InterfaceText(pText, padding, padding, pWidth - (padding * 2), pHeight - (padding * 2), pTextAnchor);
	panelText->SetColor(sf::Color::Black);
}

void InterfacePanel::Draw(sf::RenderWindow* pWindow, sf::View pCamView, sf::FloatRect* pParentRect)
{
	Interface::Draw(pWindow, pCamView);

	background.setPosition(worldPos);
	pWindow->draw(background);
	
	if(panelText)
	{
		sf::FloatRect parentRect = background.getGlobalBounds();
		panelText->Draw(pWindow, pCamView, &parentRect);
	}
}

void InterfacePanel::SetText(std::string pText)
{
	if(panelText)
	{
		panelText->SetText(pText);
	}
}

void InterfacePanel::SetFontSize(uint pFontSize)
{
	if(panelText)
	{
		panelText->SetFontSize(pFontSize);
	}
}

void InterfacePanel::SetTextColor(sf::Color pColor)
{
	if(panelText)
	{
		panelText->SetColor(pColor);
	}
}
