#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "IObserver.h"
#include "InterfaceButton.h"
#include "InterfaceProgressBar.h"

class GameScene : public Scene
{
	
private:
	class Camera* camera;
	class Player* player;
	std::vector<class Enemy*> enemies;

	//UI
	sf::RectangleShape remainingHealth;
	sf::Font font;

	InterfaceProgressBar* healthBar;
	InterfacePanel* deathPopup;
	InterfacePanel* score;
	InterfaceText* kills;

	sf::RenderWindow* window;
	sf::Clock worldTimer;
	sf::Clock collisionTimer;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	int intScore;
	//bool dead;

	std::map<std::string, GameObject*> objectsInScene;

	void spawnEnemy();

public:
	GameScene(sf::RenderWindow * window_);
	~GameScene();

	bool Initialize();
	void Destroy();
	void HandleEvents(const sf::Event event);
	void Update();
	void Render();

	bool SetBackground(std::string textureName);
};

#endif // !GAMESCENE_H