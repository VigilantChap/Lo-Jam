#include "GameManager.h"
#include "SFML.h"
#include "SFWindow.h"
#include "Scene.h"
#include "Menu.h"
#include "GameScene.h"


GameManager::GameManager()
{
	window = nullptr;
}

bool GameManager::Initialize() {
	window = new SFWindow(800, 600, "HiJam");

	if (!window->Initialize()) {
		Destroy();
		return false;
	}

	scene = new GameScene(window->getRenderWindow(), "GrasslandTiles.png");
	if (!scene->Initialize()){
		Destroy();
		return false;
	}

	return true;
}

GameManager::~GameManager()
{
}

void GameManager::Destroy() {
	delete window;
	window = nullptr;
}

void GameManager::Run() {
	bool isRunning = true;
	sf::Event event;

	while (isRunning) {
		
		while (window->getRenderWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window->getRenderWindow()->close();
				isRunning = false;
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window->getRenderWindow()->close();
					isRunning = false;
				}
			}

			scene->HandleEvents(event);
		}

		scene->Update();
		scene->Render();
		
	}
}
