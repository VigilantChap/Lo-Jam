#include "GameScene.h"
#include "Camera.h"
#include "GameObject.h"
#include "Entity.h"
#include "Player.h"
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
	player->LoadTexture("character_placeholder.png");

	

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
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::S))
		player->setPosition(player->getPosition() + sf::Vector2f(0.0f, 10.0f));
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::W))
		player->setPosition(player->getPosition() + sf::Vector2f(0.0f, -10.0f));
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::A))
		player->setPosition(player->getPosition() + sf::Vector2f(-10.0f, 0.0f));
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::D))
		player->setPosition(player->getPosition() + sf::Vector2f(10.0f, 0.0f));
}

void GameScene::Update() {
	camera->Update();
	
}

void GameScene::Render() {
	
	window->clear();
	camera->Render();
	window->draw(backgroundSprite);
	player->draw(*window);
	window->display();
}

bool GameScene::SetBackground(std::string textureName)
{
	if (!backgroundTexture.loadFromFile(textureName)) {
		std::cout << "Could not load background image.";
		return false;
	}

	backgroundSprite.setTexture(backgroundTexture);
	return true;
}
