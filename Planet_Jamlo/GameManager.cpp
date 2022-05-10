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
	
	window = new SFWindow(1920, 1080, "Planet Jamlo");

	if (!window->Initialize()) {
		Destroy();
		return false;
	}

	scene = new Menu(window->getRenderWindow());
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
	delete scene;
	scene = nullptr;

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

		if (scene->changeScene) {
			scene->Destroy();
			if (!scene->sceneName.compare("Menu")) {
				delete scene;
				scene = new GameScene(window->getRenderWindow());
			}
			else if (!scene->sceneName.compare("GameScene")) {
				delete scene;
				scene = new Menu(window->getRenderWindow());
			}

			if (!scene->Initialize()) {
				printf("Error loading game scene.\n");
				Destroy();
			}
		}

		if(scene->quit) {
			scene->Destroy();
			window->getRenderWindow()->close();
			isRunning = false;
		}
		
	}

}
