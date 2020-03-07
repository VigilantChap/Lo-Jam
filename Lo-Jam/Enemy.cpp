#include "Enemy.h"
#include <cstdlib>
#ifndef ENEMYSTATICVARIABLES
#define ENEMYSTATICVARIABLES
sf::Clock Enemy::timelapse;
#endif // !ENEMYSTATICVARIABLES

Enemy::Enemy(std::string ID) : Entity::Entity(ID)
{
	sourceRectImage = sf::IntRect(0, 0, 100, 100);
	setTextureRect(sourceRectImage);
	maxSpeed = 1;
	speed = 1;
	isTriggered = false;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Entity::Update();
	if (abs(playerPosition.x) < 200|| abs(playerPosition.y) < 200)
	{
		isTriggered = true;
	}
	else
	{
		isTriggered = false;
	}
	
	if (Enemy::timelapse.getElapsedTime().asSeconds() > 0.5f)
	{
		if (isTriggered)
		{
			sourceRectImage.top = 0;

			if (sourceRectImage.left >= 500)
				sourceRectImage.left = 0;
			else
				sourceRectImage.left += 100;

			setTextureRect(sourceRectImage);
		}
		else
		{
			sourceRectImage.top = 100;
			if (sourceRectImage.left >= 300) 
				sourceRectImage.left = 0;
			else 
				sourceRectImage.left += 100;

			setTextureRect(sourceRectImage);
		}
		Enemy::timelapse.restart();
	}
	
}

void Enemy::SetPlayerPosition(sf::Vector2<float> position)
{
	playerPosition = position;
	
	printf("%f\n", playerPosition.x);
}

/*
	if (Player::playerAnimTimer.getElapsedTime().asSeconds() > 0.5f) {

		//idle
		if (magnitude == 0) {
			sourceRectImg.top = 0;

			if (sourceRectImg.left >= 300)
				sourceRectImg.left = 0;
			else
				sourceRectImg.left += 100;

			setTextureRect(sourceRectImg);
		}
*/