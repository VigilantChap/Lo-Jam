#include "Enemy.h"

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
	if (destination.x < 100 || destination.y < 100)
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

			if (sourceRectImage.left >= 600)
				sourceRectImage.left = 0;
			else
				sourceRectImage.left += 100;

			setTextureRect(sourceRectImage);
		}
		else
		{
			sourceRectImage.top = 400;
			if (sourceRectImage.left >= 500) 
				sourceRectImage.left = 0;
			else 
				sourceRectImage.left += 100;

			setTextureRect(sourceRectImage);
		}
	}

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