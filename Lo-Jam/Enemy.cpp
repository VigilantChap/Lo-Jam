#include "Enemy.h"
#include "Camera.h"
#include <cstdlib>

#ifndef ENEMYSTATICVARIABLES
#define ENEMYSTATICVARIABLES
sf::Clock Enemy::timelapse;
std::default_random_engine Enemy::pgenerator;
#endif // !ENEMYSTATICVARIABLES

Enemy::Enemy(std::string ID) : Entity::Entity(ID)
{
	sourceRectImage = sf::IntRect(0, 0, 100, 100);
	setTextureRect(sourceRectImage);
	maxSpeed = 1;
	speed = 1;
	isTriggered = false;
	isPatrolling = false;
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
	
	//printf("%f\n", playerPosition.x);
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
	if (getPosition().x > cameraBounds.left && getPosition().x < cameraBounds.left + cameraBounds.width)
	{
		if (getPosition().y > cameraBounds.top && getPosition().y < cameraBounds.top + cameraBounds.height)
		{
			isVisible = true;
			return isVisible;
		}
	}
	
	isVisible = false;
	return isVisible;
}

void Enemy::Animate()
{

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
			
			StartPatrolMovementTowardsTarget();
		}
		else
		{
			sourceRectImage.top = 100;
			if (sourceRectImage.left >= 300)
				sourceRectImage.left = 0;
			else
				sourceRectImage.left += 100;

			setTextureRect(sourceRectImage);

			MoveTo(getPosition());
		}
		Enemy::timelapse.restart();
	}
}
