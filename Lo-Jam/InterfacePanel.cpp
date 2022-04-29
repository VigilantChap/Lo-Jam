#include "InterfacePanel.h"
#include <algorithm>
#include <iostream>

#pragma warning (disable: 26812)

InterfacePanel::~InterfacePanel()
{
}

InterfacePanel::InterfacePanel(std::string pText, float pWidth, float pHeight, float pX, float pY, Anchor pAnchor) :
	anchor(pAnchor),
	fillColor(sf::Color::White),
	fontStyle(sf::Text::Bold),
	fontSize(50),
	hPadding(8),
	scaleX(0.5),
	scaleY(0.5),
	plainText("")
{
	if(!font.loadFromFile("arial.ttf"))
	{
		printf("Error: cannot load font\n");
	}

	setPosition(sf::Vector2f(pX, pY));
	SetAnchor(pAnchor);

	background.setSize(sf::Vector2f(pWidth, pHeight));
	background.setOrigin(pWidth * scaleX, pHeight * scaleY);
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(2);
	background.setFillColor(fillColor);

	text = sf::Text(pText, font);
	SetText(pText);
	text.setCharacterSize(fontSize);
	text.setStyle(fontStyle);
	text.setFillColor(sf::Color::Black);
}

void InterfacePanel::SetText(std::string& pText)
{
	plainText = pText;
	uint lastSpace = 0;
	float lineWidth = 0;
	float lineHeight = 0;
	float wordWidth = 0;
	float advance = 0;
	float maxWidth = background.getSize().x - (hPadding * 2);
	
	for(uint i = 0; i <= pText.size(); i++)
	{
		if(lineWidth < maxWidth)
		{
			sf::Glyph glyph = font.getGlyph(uint(pText[i]), fontSize, fontStyle);
			advance = glyph.advance;
			wordWidth += advance;
			lineWidth += advance;
			lineHeight = std::max(lineHeight, -glyph.bounds.top);
			
			//std::cout << pText[i] << " " << -glyph.bounds.top << " " << glyph.bounds.height << std::endl;
		}
		else
		{
			i--; //we were too wide, need to try to add this character again
			if(wordWidth < maxWidth) //we have spaces so can wrap text normally
			{
				pText.replace(lastSpace, 1, "\n");
				lineWidth = wordWidth;
			}
			else //no spaces in a single line of text, add new line once we reach max width
			{
				pText.insert(i, 1, '\n');
				lineWidth = 0;
			}
		}
		if(pText[i] == ' ')
		{
			lastSpace = i;
			wordWidth = 0;
		}
	}
	
	text.setString(pText);
	text.setOrigin(text.getLocalBounds().width * scaleX, fontSize - lineHeight * scaleY);
}

void InterfacePanel::Draw(sf::RenderWindow* pWindow, sf::View pCamView)
{
	const sf::Vector2f newPos = pCamView.getCenter() - (sf::Vector2f(pCamView.getSize().x / 2, pCamView.getSize().y / 2)) + getPosition();
	background.setPosition(newPos);
	pWindow->draw(background);

	text.setPosition(newPos);
	pWindow->draw(text);
}

void InterfacePanel::SetFontSize(uint pFontSize)
{
	fontSize = pFontSize;
	text.setCharacterSize(fontSize);
	SetText(plainText);
}

void InterfacePanel::SetAnchor(Anchor pAnchor)
{
	anchor = pAnchor;
	scaleX = fmodf(anchor, 3) / 2;
	scaleY = floor(anchor / 3) / 2;
}
