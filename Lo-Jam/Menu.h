#ifndef MENU_H
#define MENU_H

#include "Scene.h"

class Menu : public Scene
{
private:
	sf::RenderWindow * window;

public:
	Menu(sf::RenderWindow * window_);
	~Menu();

	bool Initialize();
	void Destroy();
	void HandleEvents(sf::Event event) const;
	void Update();
	void Render();
};


#endif // !MENU_H