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

	auto centre = window->getView().getCenter();

	// Create title text
	titleText = new InterfaceText("Planet Jamlo", centre.x, 210);
	titleText->SetColor(sf::Color::Cyan, sf::Color(0, 0, 0, 75));

	//Background image
	backdrop = new GameObject("menuBackground");
	backdrop->LoadTexture("Assets/title_Background.png");
	backdrop->scale(1.25, 1.25);
	backdrop->setPosition(centre);
	
	//Create playButton
	playButton = new InterfaceButton("Play", [&]() { PlayButtonPressed(); }, centre.x, 525, Interface::BOT_CENTER);

	//Create quitButton
	quitButton = new InterfaceButton("Quit", [&]() { QuitButtonPressed(); }, centre.x, playButton->getPosition().y + 50, Interface::TOP_CENTER);

	return true;
}

void Menu::Destroy() {
	delete backdrop;
	backdrop = nullptr;

	delete titleText;
	titleText = nullptr;

	delete playButton;
	playButton = nullptr;

	delete quitButton;
	quitButton = nullptr;
}

void Menu::PlayButtonPressed(){
	changeScene = true;
}

void Menu::QuitButtonPressed() {
	quit = true;
}

void Menu::HandleEvents(const sf::Event event) {

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