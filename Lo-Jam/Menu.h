#ifndef MENU_H
#define MENU_H

#include "Scene.h"
#include "InterfaceButton.h"

class Menu : public Scene
{
private:
	sf::RenderWindow * window;
	class GameObject* backdrop;
	sf::Font font;
	sf::Text title, playText, quitText;

	InterfaceText * titleText;
	InterfaceButton * playButton, * quitButton;

	void PlayButtonPressed();
	void QuitButtonPressed();

public:
	Menu(sf::RenderWindow * window_);
	~Menu();

	bool Initialize();
	void Destroy();
	void HandleEvents(const sf::Event event);
	void Update();
	void Render();

};


#endif // !MENU_H