#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"

class GameScene : public Scene
{
	
private:
	class Camera* camera;
	class Player* player;
	sf::RenderWindow* window;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	std::string	backgroundTextureName;

	sf::View view;
	
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