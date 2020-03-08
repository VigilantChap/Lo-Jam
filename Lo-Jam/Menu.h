#ifndef MENU_H
#define MENU_H

#include "Scene.h"

class Menu : public Scene
{
private:
	sf::RenderWindow * window;
	sf::RectangleShape backdrop;
	sf::RectangleShape playButton, quitButton;
	sf::Font font;
	sf::Text title, playText, quitText;

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