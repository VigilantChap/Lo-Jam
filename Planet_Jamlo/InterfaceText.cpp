#include "InterfaceText.h"

#pragma warning (disable: 26812)

InterfaceText::~InterfaceText()
{
}

InterfaceText::InterfaceText(std::string pText, float pX, float pY, float pWidth, float pHeight, Anchor pAnchor) :
	fontStyle(sf::Text::Bold),
	fontSize(180),
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
	text.setCharacterSize(fontSize);
	text.setStyle(fontStyle);
	text.setFillColor(sf::Color::Cyan);
	SetText(pText);
}

void InterfaceText::SetText(std::string pText)
{
	plainText = pText;
	sf::Glyph glyph;
	uint lastSpace = 0;
	uint lineChars = 0;
	float lastLineWidth = 0;
	float maxLineWidth = 0;
	float lineWidth = 0;
	float lineHeight = 0;
	float lineOffset = 0;
	float wordWidth = 0;
	float advance = 0;

	for(uint i = 0; i < pText.size() + 1; i++) //need to loop one extra time in case the last character is outside bounds
	{
		//only wrap if width limit is set, and we are over it, and at least a single character has been added to the line (to prevent infinite loops)
		if(textWidth > 0 && lineWidth > textWidth && lineChars > 1)
		{
			if(wordWidth < textWidth) //we have spaces so can wrap text normally
			{
				pText.replace(lastSpace, 1, "\n"); //because we replace a space character rather than inserting new, i does not need to be incremented
				lineWidth = wordWidth;
				lineChars = i - 1 - lastSpace;
			}
			else //no spaces in a single line of text, add new line once we reach max width
			{
				pText.insert(i - 1, 1, '\n');
				lastLineWidth = lineWidth - advance;
				wordWidth = advance;
				lineWidth = wordWidth;
				lineChars = 1;
				i++; //our last character got dropped to a new line by adding a new line character in front, process the next character
			}
			maxLineWidth = std::max(maxLineWidth, lastLineWidth);
		}

		if(i < pText.size())
		{
			glyph = font.getGlyph(uint(pText[i]), fontSize, fontStyle);
			advance = glyph.advance;
			wordWidth += advance;
			lineWidth += advance;
			lineHeight = std::max(lineHeight, -glyph.bounds.top);
			lineOffset = std::min(glyph.bounds.left, lineOffset);
			lineChars++;

			if(pText[i] == ' ')
			{
				lastSpace = i;
				wordWidth = 0;
				lastLineWidth = lineWidth - advance;
			}
		}
	}
	maxLineWidth = std::max(maxLineWidth, lineWidth);

	text.setString(pText);
	text.setOrigin((maxLineWidth - lineOffset) * scaleWidth, fontSize - lineHeight * (1 - scaleHeight));
	//printf("%f\t%f\n", maxLineWidth, text.getLocalBounds().width);
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

void InterfaceText::SetColor(sf::Color pColor, sf::Color pOutlineColor)
{
	text.setFillColor(pColor);

	if(pOutlineColor != sf::Color::Transparent)
	{
		text.setOutlineThickness(1 + std::floor(fontSize / 30));
		text.setOutlineColor(pOutlineColor);
	}
	else
	{
		text.setOutlineThickness(0);
	}
}
