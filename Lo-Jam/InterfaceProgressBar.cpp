#include "InterfaceProgressBar.h"

#pragma warning (disable: 26812)

InterfaceProgressBar::~InterfaceProgressBar()
{
}

InterfaceProgressBar::InterfaceProgressBar(float pProgress, float pWidth, float pHeight, float pX, float pY, Anchor pAnchor, bool pVertical) :
	maxProgress(100),
	vertical(pVertical),
	progressText(""),
	InterfacePanel("", pWidth, pHeight, pX, pY, pAnchor)
{
	fill.setOrigin(0, pHeight * scaleHeight);
	fill.setOutlineThickness(0);
	fill.setFillColor(sf::Color::Red);

	SetFontSize(80);
	SetProgress(pProgress);
}

void InterfaceProgressBar::Draw(sf::RenderWindow* pWindow, sf::View pCamView, sf::FloatRect* pParentRect)
{
	Interface::Draw(pWindow, pCamView); //intentionally skip draw for InterfacePanel, do everything here to correct draw order

	background.setPosition(worldPos);
	pWindow->draw(background);

	worldPos.x -= background.getSize().x * scaleWidth;
	fill.setPosition(worldPos);
	pWindow->draw(fill);

	if(panelText)
	{
		sf::FloatRect parentRect = background.getGlobalBounds();
		panelText->Draw(pWindow, pCamView, &parentRect);
	}
}

void InterfaceProgressBar::SetProgress(float pProgress, bool pActualValue)
{
	if(pActualValue)
	{
		pProgress /= maxProgress;
	}

	if(progress == pProgress)
	{
		return;
	}
	progress = pProgress;

	sf::Vector2f fillSize = background.getSize();
	vertical ? (fillSize.y *= progress) : (fillSize.x *= progress);
	fill.setSize(fillSize);

	UpdateProgressText();
}

void InterfaceProgressBar::SetProgressText(std::string pText)
{
	if(progressText == pText)
	{
		return;
	}

	progressText = pText;

	if(progressText.empty())
	{
		SetText(progressText);
	}
	else
	{
		UpdateProgressText();
	}
}

void InterfaceProgressBar::UpdateProgressText()
{
	if(!progressText.empty())
	{
		static const int maxSize = 1024;
		static char buffer[maxSize];
		snprintf(buffer, maxSize, progressText.c_str(), (uint)(progress * maxProgress));
		SetText(buffer);
	}
}