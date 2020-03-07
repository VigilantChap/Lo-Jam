#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
class Enemy : public Entity
{
public:
	Enemy(std::string ID);
	~Enemy(); 

	void Update();
	
	static sf::Clock timelapse;
	void SetPlayerPosition(sf::Vector2<float>);
private:
	sf::IntRect sourceRectImage;
	sf::Vector2<float> playerPosition;
	bool isTriggered;
};


#endif // !ENEMY_H
