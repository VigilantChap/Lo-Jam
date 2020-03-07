#include "GameScene.h"
#include "Camera.h"
#include "GameObject.h"
#include "Entity.h"
#include "Player.h"
#include "Dog.h"
#include <iostream>


GameScene::GameScene(sf::RenderWindow * window_) : GameScene(window, "")
{
}

GameScene::GameScene(sf::RenderWindow * window_, std::string backgroundTexture) : window(window_), backgroundTextureName(backgroundTexture)
{	
}


GameScene::~GameScene()
{
}

bool GameScene::Initialize() {
	player = new Player("player");
	player->LoadTexture("Assets/PlayerSpriteSheet.png");
	player->scale(3, 3);
	player->updateCentre();


	camera = new Camera(window);
	camera->SetAsMainView();
	camera->SetFollowTarget(player);
	
	if (backgroundTextureName != "") {
		if (!SetBackground(backgroundTextureName)) {
			Destroy();
			return false;
		}
	}
	
	return true;
}

void GameScene::Destroy() {

}

void GameScene::HandleEvents(sf::Event event) const {

	camera->HandleEvents(event);

	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
			player->MoveTo(window->mapPixelToCoords(pixelPos));
		}

	}	
	
}

void GameScene::Update() {
	camera->Update();
	player->Update();
}

void GameScene::Render() {
	
	window->clear();
	camera->Render();
	window->draw(backgroundSprite);
	window->draw(*player->getDog());
	window->draw(*player);
	window->display();
	
}

bool GameScene::SetBackground(std::string textureName)
{
	if (!backgroundTexture.loadFromFile(textureName)) {
		std::cout << "Could not load background image.";
		return false;
	}

	backgroundTexture.setRepeated(true);
	sf::FloatRect fBoundary(0.0f, 0.0f, 5000.0f, 5000.0f);
	sf::IntRect iBoundary(fBoundary);
	backgroundSprite = sf::Sprite(backgroundTexture, iBoundary);
	backgroundSprite.setPosition(fBoundary.left - camera->GetView().getSize().x, fBoundary.top - 5000.0f + camera->GetView().getSize().y);

	
	return true;
}
