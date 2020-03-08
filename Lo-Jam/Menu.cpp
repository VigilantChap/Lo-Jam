#include "Menu.h"



Menu::Menu(sf::RenderWindow * window_) : window(window_)
{
}


Menu::~Menu()
{
}

bool Menu::Initialize() {
	changeScene = false;

	backdrop = sf::RectangleShape(sf::Vector2f(window->getSize()));
	backdrop.setPosition(0, 0);
	backdrop.setFillColor(sf::Color::Black);
	
	playButton = sf::RectangleShape(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 10));
	playButton.setOrigin(playButton.getSize().x / 2, playButton.getSize().y / 2);
	playButton.setPosition(window->getSize().x / 2, (window->getSize().y / 5) * 2);
	playButton.setFillColor(sf::Color::Cyan);

	quitButton = sf::RectangleShape(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 10));
	quitButton.setOrigin(quitButton.getSize().x / 2, quitButton.getSize().y / 2);
	quitButton.setPosition(window->getSize().x / 2, (window->getSize().y / 5) * 3);
	quitButton.setFillColor(sf::Color::Cyan);

		

	return true;
}

void Menu::Destroy() {

}

void Menu::HandleEvents(const sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
			//if clicked on play button
			if (pixelPos.x <= playButton.getPosition().x + (playButton.getSize().x / 2)
				&& pixelPos.x >= playButton.getPosition().x - (playButton.getSize().x / 2)
				&& pixelPos.y <= playButton.getPosition().y + (playButton.getSize().y / 2)
				&& pixelPos.y >= playButton.getPosition().y - (playButton.getSize().y / 2))
			{
				changeScene = true;
			}

			if (pixelPos.x <= quitButton.getPosition().x + (quitButton.getSize().x / 2)
				&& pixelPos.x >= quitButton.getPosition().x - (quitButton.getSize().x / 2)
				&& pixelPos.y <= quitButton.getPosition().y + (quitButton.getSize().y / 2)
				&& pixelPos.y >= quitButton.getPosition().y - (quitButton.getSize().y / 2))
			{
				quit = true;
			}
		}

	}
}

void Menu::Update() {

}

void Menu::Render() {
	window->clear();

	window->draw(backdrop);
	window->draw(playButton);
	window->draw(quitButton);

	window->display();
}