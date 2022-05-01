#ifndef INTERFACE_H
#define INTERFACE_H

#include "SFML.h"
#include <functional>
#include <algorithm>

typedef unsigned int uint;
typedef std::function<void()> Callback;

class Interface : public sf::Sprite
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

	Interface(float pX = 0, float pY = 0, Anchor pAnchor = Anchor::MID_CENTER);
	~Interface();

	virtual void Draw(sf::RenderWindow* pWindow, sf::View pCamView, sf::FloatRect* pParentRect = nullptr);

	void SetAnchor(Anchor pAnchor);

protected:
	sf::Vector2f worldPos;
	Anchor anchor;
	float scaleWidth;
	float scaleHeight;
};

#endif // INTERFACE_H