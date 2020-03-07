#ifndef SFWINDOW_H
#define SFWINDOW_H
#include "SFML.h"

class SFWindow
{
private:
	sf::RenderWindow * window;
	const char* title;
	int w, h;

public:
	SFWindow(int w_, int h_, const char* title_);
	bool Initialize();
	~SFWindow();
	void Destroy();

	inline sf::RenderWindow * getRenderWindow() { return window; }
};

#endif // SFWINDOW_H