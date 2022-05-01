#include "Menu.h"
#include "MusicPlayer.h"
#include "GameObject.h"

Menu::Menu(sf::RenderWindow * window_) : window(window_)
{
}


Menu::~Menu()
{
}

bool Menu::Initialize() {
	sceneName = "Menu";
	changeScene = false;

	//if (!font.loadFromFile("arial.ttf")) printf("Error: cannot load font\n");

	auto centre = window->getView().getCenter();
	//auto size = window->getView().getSize();

	// Create title text
	//title = sf::Text("Planet Jamlo", font);
	//title.setCharacterSize(120);
	//title.setStyle(sf::Text::Bold);
	//title.setFillColor(sf::Color::Cyan);
	//title.setOrigin(title.getGlobalBounds().width / 2.0f, title.getGlobalBounds().height / 2.0f);
	//title.setPosition(centre.x, centre.y / 3.0f);
	//title.setOutlineThickness(5);
	//sf::Color outlineColour;
	//outlineColour.a = 75;
	//title.setOutlineColor(outlineColour);

	titleText = new InterfaceText("Planet Jamlo", centre.x, 210);
	titleText->SetColor(sf::Color::Cyan, sf::Color(0, 0, 0, 75));
	
	//sf::Texture s;
	//if (!s.loadFromFile("Assets/title_Background.png")) printf("Could not load menu background image.\n");
	backdrop = new GameObject("menuBackground");
	backdrop->LoadTexture("Assets/title_Background.png");
	backdrop->scale(1.25, 1.25);
	backdrop->setPosition(window->getView().getCenter());
	
	//Create playButton
	//playButton = sf::RectangleShape(sf::Vector2f(centre.x, window->getView().getSize().y / 10.0f));
	//playButton.setOrigin(playButton.getSize().x / 2.0f, playButton.getSize().y / 2.0f);
	//playButton.setPosition(centre.x, centre.y - playButton.getSize().y);
	//playButton.setFillColor(sf::Color::Cyan);
	//playButton text
	//playText = sf::Text("Play", font);
	//playText.setCharacterSize(40);
	//playText.setStyle(sf::Text::Bold);
	//playText.setFillColor(sf::Color::Black);
	//playText.setOrigin(playText.getGlobalBounds().width / 2.0f, playText.getGlobalBounds().height);

	playButton = new InterfaceButton("Play", [&]() {PlayButtonPressed(); }, centre.x, 525, Interface::BOT_CENTER);

	//Create quitButton
	//quitButton = sf::RectangleShape(sf::Vector2f(window->getView().getSize().x / 2.0f, window->getView().getSize().y / 10.0f));
	//quitButton.setOrigin(quitButton.getSize().x / 2.0f, quitButton.getSize().y / 2.0f);
	//quitButton.setPosition(centre.x, centre.y + quitButton.getSize().y);
	//quitButton.setFillColor(sf::Color::Cyan);
	//quitButton text
	//quitText = sf::Text("Quit", font);
	//quitText.setCharacterSize(40);
	//quitText.setStyle(sf::Text::Bold);
	//quitText.setFillColor(sf::Color::Black);
	//quitText.setOrigin(quitText.getLocalBounds().width / 2.0f, quitText.getLocalBounds().height);

	quitButton = new InterfaceButton("Quit", [&]() {QuitButtonPressed(); }, centre.x, playButton->getPosition().y + 50, Interface::TOP_CENTER);

	return true;
}

void Menu::Destroy() {
	delete backdrop;
	backdrop = nullptr;
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
	backdrop->Update();
}

void Menu::Render() {
	window->clear();

	window->draw(*backdrop);

	titleText->Draw(window, window->getView());
	playButton->Draw(window, window->getView());
	quitButton->Draw(window, window->getView());

	window->display();
}