#include "Menu.h"
#include "MusicPlayer.h"

Menu::Menu(sf::RenderWindow * window_) : window(window_)
{
}


Menu::~Menu()
{
}

bool Menu::Initialize() {
	sceneName = "Menu";
	changeScene = false;

	if (!font.loadFromFile("arial.ttf")) printf("Error: cannot load font\n");

	auto centre = window->getView().getCenter();
	auto size = window->getView().getSize();

	// Create title text
	title = sf::Text("Symptomania", font);
	title.setCharacterSize(75);
	title.setStyle(sf::Text::Bold);
	title.setFillColor(sf::Color::Cyan);
	title.setOrigin(title.getGlobalBounds().width / 2.0f, title.getGlobalBounds().height / 2.0f);
	title.setPosition(centre.x, centre.y / 3.0f);

	backdrop = sf::RectangleShape(sf::Vector2f(window->getSize()));
	backdrop.setPosition(0, 0);
	backdrop.setFillColor(sf::Color::Black);
	
	//Create playButton
	//playButton = sf::RectangleShape(sf::Vector2f(centre.x, window->getView().getSize().y / 10.0f));
	//playButton.setOrigin(playButton.getSize().x / 2.0f, playButton.getSize().y / 2.0f);
	//playButton.setPosition(centre.x, centre.y - playButton.getSize().y);
	//playButton.setFillColor(sf::Color::Cyan);
	//playButton text
	playText = sf::Text("Play", font);
	playText.setCharacterSize(40);
	playText.setStyle(sf::Text::Bold);
	playText.setFillColor(sf::Color::Black);
	playText.setOrigin(playText.getGlobalBounds().width / 2.0f, playText.getGlobalBounds().height);

	playButton = new InterfaceButton("Play", [&]() {PlayButtonPressed(); }, centre.x, 525);

	//Create quitButton
	//quitButton = sf::RectangleShape(sf::Vector2f(window->getView().getSize().x / 2.0f, window->getView().getSize().y / 10.0f));
	//quitButton.setOrigin(quitButton.getSize().x / 2.0f, quitButton.getSize().y / 2.0f);
	//quitButton.setPosition(centre.x, centre.y + quitButton.getSize().y);
	//quitButton.setFillColor(sf::Color::Cyan);
	//quitButton text
	quitText = sf::Text("Quit", font);
	quitText.setCharacterSize(40);
	quitText.setStyle(sf::Text::Bold);
	quitText.setFillColor(sf::Color::Black);
	quitText.setOrigin(quitText.getLocalBounds().width / 2.0f, quitText.getLocalBounds().height);

	quitButton = new InterfaceButton("Quit", [&]() {QuitButtonPressed(); }, centre.x, playButton->getPosition().y + 100 + 50);

	return true;
}

void Menu::Destroy() {

}

void Menu::PlayButtonPressed(){
	changeScene = true;
}

void Menu::QuitButtonPressed() {
	quit = true;
}

void Menu::HandleEvents(const sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
			pixelPos = sf::Vector2i(window->mapPixelToCoords(pixelPos).x, window->mapPixelToCoords(pixelPos).y);

			//if (playButton.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
			//{
			//	MusicPlayer::PlaySelectSound();
			//	changeScene = true;
			//}

			//if (quitButton.getGlobalBounds().contains(pixelPos.x, pixelPos.y))
			//{
			//	MusicPlayer::PlaySelectSound();
			//	quit = true;
			//}
		}

	}

	playButton->HandleEvents(event);
	quitButton->HandleEvents(event);

	if (event.type == sf::Event::Resized) {
		Initialize();
	}
}

void Menu::Update() {

}

void Menu::Render() {
	window->clear();

	window->draw(backdrop);
	
	playButton->Draw(window, window->getView());
	quitButton->Draw(window, window->getView());
	
	window->draw(title);

	window->display();
}