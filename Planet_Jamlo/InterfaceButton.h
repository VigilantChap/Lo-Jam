#ifndef INTERFACE_BUTTON_H
#define INTERFACE_BUTTON_H

#include "InterfacePanel.h"

class InterfaceButton : public InterfacePanel
{
public:
	InterfaceButton(std::string pText, Callback pPressCallback, float pX = 0, float pY = 0, Anchor pAnchor = Anchor::MID_CENTER);
	~InterfaceButton();

	void HandleEvents(const sf::Event pEvent);
	void SetFocused(bool pFocused);

protected:
	bool focused;
	sf::Color focusedColor;

	Callback pressCallback;
};

#endif // INTERFACE_BUTTON_H