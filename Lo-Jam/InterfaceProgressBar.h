#ifndef INTERFACE_PROGRESSBAR_H
#define INTERFACE_PROGRESSBAR_H

#include "InterfacePanel.h"

class InterfaceProgressBar : public InterfacePanel
{
public:
	InterfaceProgressBar(float pProgress, float pWidth, float pHeight, float pX = 0, float pY = 0, Anchor pAnchor = Anchor::MID_CENTER, bool pVertical = false);
	~InterfaceProgressBar();

	void Draw(sf::RenderWindow* pWindow, sf::View pCamView, sf::FloatRect* pParentRect = nullptr) override;
	void SetProgress(float pProgress, bool pActualValue = false); // pProgress is 0 to 1, unless pActualValue is true
	void SetProgressText(std::string pText);
	void UpdateProgressText();

protected:
	sf::RectangleShape fill;
	float maxProgress;
	float progress;
	bool vertical;
	std::string progressText;
};

#endif // INTERFACE_PROGRESSBAR_H