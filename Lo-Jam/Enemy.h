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
private:
	sf::IntRect sourceRectImage;
	bool isTriggered;
};


#endif // !ENEMY_H
