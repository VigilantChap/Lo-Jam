#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "IObserver.h"
#include "InterfaceButton.h"

class GameScene : public Scene
{
	
private:
	class Camera* camera;
	class Player* player;
	std::vector<class Enemy*> enemies;


	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	std::string	backgroundTextureName;

	//UI
	sf::RectangleShape healthBar, remainingHealth, deathNotif;
	sf::Font font;
	sf::Text deathNotifText;
	InterfacePanel *score;
	int intScore;
	void UpdateHealthBar();

	sf::RenderWindow* window;
	sf::Clock worldTimer;
	sf::Clock collisionTimer;

	bool triggered;
	bool dead;

	std::map<std::string, GameObject*> objectsInScene;

	void spawnEnemy();

public:
	GameScene(sf::RenderWindow * window_);
	GameScene(sf::RenderWindow * window_, std::string backgroundTexture);
	~GameScene();

	bool Initialize();
	void Destroy();
	void HandleEvents(const sf::Event event);
	void Update();
	void Render();

	bool SetBackground(std::string textureName);
};

#endif // !GAMESCENE_H