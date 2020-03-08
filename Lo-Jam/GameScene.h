#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"

class GameScene : public Scene
{
	
private:
	class Camera* camera;
	class Player* player;
	class Entity* dog;
	class Enemy* tempEnemy;
	std::vector<Enemy*> enemies;


	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	std::string	backgroundTextureName;

	//UI
	sf::RectangleShape healthBar, remainingHealth;
	void UpdateHealthBar();

	sf::RenderWindow* window;
	sf::Clock worldTimer;
	sf::Clock collisionTimer;

	bool triggered;
	
public:
	GameScene(sf::RenderWindow * window_);
	GameScene(sf::RenderWindow * window_, std::string backgroundTexture);
	~GameScene();

	bool Initialize();
	void Destroy();
	void HandleEvents(sf::Event event) const;
	void Update();
	void Render();

	bool SetBackground(std::string textureName);
};

#endif // !GAMESCENE_H