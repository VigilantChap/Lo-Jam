#include "Enemy.h"
#include "Camera.h"
#include <cstdlib>

#ifndef ENEMYSTATICVARIABLES
#define ENEMYSTATICVARIABLES

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
	Animate();
}

void Enemy::SetPlayerPosition(sf::Vector2<float> position)
{
	playerPosition = position;
}

void Enemy::StartPatrolMovementTowardsTarget()
{
	//Distributes Values
	std::normal_distribution<double> distributionX(playerPosition.x - getPosition().x, 100);
	std::normal_distribution<double> distributionY(playerPosition.y - getPosition().y, 100);
	//Ensures that destination is always towards target
	destination.x = distributionX(pgenerator) + playerPosition.x - getPosition().x * 2;
	destination.y = distributionY(pgenerator) + playerPosition.y - getPosition().y * 2;
	
	MoveTo(destination);
}

bool Enemy::InView(Camera &camera_)
{
	/*Setting Boundaries for InView*/
	camera = &camera_;
	sf::Vector2<float> cameraPosition;

	cameraPosition.x = camera->GetView().getCenter().x - camera->GetView().getSize().x / 2.0f;
	cameraPosition.y = camera->GetView().getCenter().y - camera->GetView().getSize().y / 2.0f;

	sf::FloatRect cameraBounds(cameraPosition,camera->GetView().getSize());

	/***********************If In Visible Bounds**********************/
	if (getPosition().x > cameraBounds.left && getPosition().x < cameraBounds.left + cameraBounds.width)
	{
		if (getPosition().y > cameraBounds.top && getPosition().y < cameraBounds.top + cameraBounds.height)
		{
			isVisible = true;
			return isVisible;
		}
	}
	/*******************If Not In Visible Bounds**********************/
	isVisible = false;
	return isVisible;
}//--end InView()

void Enemy::Animate()
{
	if (Enemy::timelapse.getElapsedTime().asSeconds() > 0.5f)
	{
		if (isTriggered) //Evil Mode
		{
			sourceRectImage.top = 0;

			if (sourceRectImage.left >= 500)
				sourceRectImage.left = 0;
			else
				sourceRectImage.left += 100;
			//--end if(sourceRectImage.left >= 500)
			setTextureRect(sourceRectImage);
			StartPatrolMovementTowardsTarget();
		}
		else // Good Mode 
		{
			sourceRectImage.top = 100;
			if (sourceRectImage.left >= 300)
				sourceRectImage.left = 0;
			else
				sourceRectImage.left += 100;
			//--end if(sourceRectImage.left >= 300)
			setTextureRect(sourceRectImage);
			MoveTo(getPosition()); //Stop Movement
		}//--end if(isTriggered)

		Enemy::timelapse.restart(); //Restart Clock for Frame Count
	}//--end if(Enemy::timelapse.getElapsedTime().asSeconds() > 0.5f)
}//--end Anime()
