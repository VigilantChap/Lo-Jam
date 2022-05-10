#include "SFWindow.h"
#include "SFML.h"


SFWindow::SFWindow(int w_, int h_, const char* title_) : w(w_), h(h_), title(title_)
{
	window = nullptr;
}

bool SFWindow::Initialize(){
	window = new sf::RenderWindow(sf::VideoMode(w, h), title);

	if (window == nullptr) {
		Destroy();
		return false;
	}

	return true;
}

SFWindow::~SFWindow()
{

}

void SFWindow::Destroy() {
	delete window;
	window = nullptr;
}

