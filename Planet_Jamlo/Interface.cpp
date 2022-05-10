#include "Interface.h"

#pragma warning (disable: 26812)

Interface::~Interface()
{
}

Interface::Interface(float pX, float pY, Anchor pAnchor)
{
	SetAnchor(pAnchor);

	setPosition(sf::Vector2f(pX, pY));
}

void Interface::Draw(sf::RenderWindow* pWindow, sf::View pCamView, sf::FloatRect* pParentRect)
{
	worldPos = pCamView.getCenter() - (sf::Vector2f(pCamView.getSize().x / 2, pCamView.getSize().y / 2)) + getPosition();
}

void Interface::SetAnchor(Anchor pAnchor)
{
	anchor = pAnchor;
	scaleWidth = fmodf(anchor, 3) / 2;
	scaleHeight = floor(anchor / 3) / 2;
}
