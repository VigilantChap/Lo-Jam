#include "InterfaceText.h"

#pragma warning (disable: 26812)

InterfaceText::~InterfaceText()
{
}

InterfaceText::InterfaceText(std::string pText, float pX, float pY, float pWidth, float pHeight, Anchor pAnchor) :
	fontColor(sf::Color::Black),
	fontStyle(sf::Text::Bold),
	fontSize(50),
	textWidth(pWidth),
	textHeight(pHeight),
	plainText(""),
	Interface(pX, pY, pAnchor)
{
	if(!font.loadFromFile("arial.ttf"))
	{
		printf("Error: cannot load font\n");
	}

	text = sf::Text(pText, font);
	SetText(pText);
	text.setCharacterSize(fontSize);
	text.setStyle(fontStyle);
	text.setFillColor(fontColor);
}

void InterfaceText::SetText(std::string& pText)
{
	plainText = pText;
	uint lastSpace = 0;
	float lineWidth = 0;
	float lineHeight = 0;
	float wordWidth = 0;
	float advance = 0;

	if(textWidth > 0)
	{
		for(uint i = 0; i <= pText.size(); i++)
		{
			if(lineWidth < textWidth)
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
				if(wordWidth < textWidth) //we have spaces so can wrap text normally
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
	}

	text.setString(pText);
	text.setOrigin(text.getLocalBounds().width * scaleWidth, fontSize - lineHeight * (1-scaleHeight));
	//printf("%f\t%f\n", GetTextWidth(), text.getLocalBounds().width);
}

void InterfaceText::Draw(sf::RenderWindow* pWindow, sf::View pCamView, sf::FloatRect* pParentRect)
{
	Interface::Draw(pWindow, pCamView, pParentRect);

	if(pParentRect)
	{
		worldPos.x = pParentRect->left + getPosition().x + (textWidth * scaleWidth);
		worldPos.y = pParentRect->top + getPosition().y + (textHeight * scaleHeight);
	}
	text.setPosition(worldPos);
	pWindow->draw(text);
}

void InterfaceText::SetFontSize(uint pFontSize)
{
	fontSize = pFontSize;
	text.setCharacterSize(fontSize);
	SetText(plainText);
}
