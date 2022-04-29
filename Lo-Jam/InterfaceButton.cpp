#include "InterfaceButton.h"
#include "MusicPlayer.h"
#include <iostream>

#pragma warning (disable: 26812)

InterfaceButton::~InterfaceButton()
{
}

InterfaceButton::InterfaceButton(std::string pText, Callback pPressCallback, float pX, float pY, Anchor pAnchor) :
	InterfacePanel(pText, 800, 100, pX, pY, pAnchor),
	focused(false),
	focusedColor(sf::Color::Cyan),
	pressCallback(pPressCallback)
{
	background.setOutlineColor(sf::Color::Yellow);
	SetFontSize(40);
}

void InterfaceButton::SetText(std::string& pText)
{
	InterfacePanel::SetText(pText);
}

void InterfaceButton::Draw(sf::RenderWindow* pWindow, sf::View pCamView)
{
	InterfacePanel::Draw(pWindow, pCamView);
}

void InterfaceButton::HandleEvents(const sf::Event pEvent)
{
	switch(pEvent.type)
	{
		case sf::Event::MouseMoved:
			SetFocused(background.getGlobalBounds().contains(pEvent.mouseMove.x, pEvent.mouseMove.y));
			break;
		case sf::Event::MouseButtonPressed:
			if(focused && pEvent.mouseButton.button == sf::Mouse::Left)
			{
				MusicPlayer::PlaySelectSound();
				pressCallback();
			}
			break;
		case sf::Event::MouseButtonReleased:
			break;
		default:
			break;
	}
}

void InterfaceButton::SetFocused(bool pFocused)
{
	if(focused == pFocused)
	{
		return;
	}

	focused = pFocused;
	background.setFillColor(focused ? focusedColor : fillColor);
}
