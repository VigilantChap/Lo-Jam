#include "Enemy.h"
#include "Camera.h"
#include <cstdlib>
#include "Animator.h"

#ifndef ENEMYSTATICVARIABLES
#define ENEMYSTATICVARIABLES
 std::default_random_engine Enemy::pgenerator;
#endif // !ENEMYSTATICVARIABLES

Enemy::Enemy(std::string ID) : Entity::Entity(ID)
{
	//LoadTexture("Assets/EnemySpriteSheet.png");
	LoadTexture("Assets/NewEnemySpriteSheet.png");
	//sourceRectImage = sf::IntRect(0, 0, 100, 100);
	//setTextureRect(sourceRectImage);

	this->scale(2, 2);

	animator = new Animator(this);
	if (!animator->Instantiate()) {
		printf("Could not instantiate %s animator.\n", ID.c_str());
		delete animator;
		animator = nullptr;
	}

	else observers.push_back(animator);

	maxSpeed = 30;
	speed = 30;
	isVisible = false;
	health = 100;
	maxHealth = 100;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Entity::Update();

}

void Enemy::HandleState() {
	Entity::HandleState();
	if (AIdelay.getElapsedTime().asSeconds() >= 0.5f) {
		StartPatrolMovementTowardsTarget();
		AIdelay.restart();
	}
}

void Enemy::SetPlayerPosition(sf::Vector2f position)
{
	playerPosition = position;
}

void Enemy::StartPatrolMovementTowardsTarget()
{

	//Distributes Values
	std::normal_distribution<float> distributionX(playerPosition.x, 1500);
	std::normal_distribution<float> distributionY(playerPosition.y, 1500);

	//Ensures that destination is always towards target
	destination.x = distributionX(pgenerator) + playerPosition.x - getPosition().x;
	destination.y = distributionY(pgenerator) + playerPosition.y - getPosition().y;
	

	MoveTo(destination);

}

//bool Enemy::InView(Camera &camera_)
//{
//	/*Setting Boundaries for InView*/
//	camera = &camera_;
//	sf::Vector2<float> cameraPosition;
//
//	cameraPosition.x = camera->GetView().getCenter().x - camera->GetView().getSize().x / 2.0f;
//	cameraPosition.y = camera->GetView().getCenter().y - camera->GetView().getSize().y / 2.0f;
//
//	sf::FloatRect cameraBounds(cameraPosition,camera->GetView().getSize());
//
//	/***********************If In Visible Bounds**********************/
//	if (getPosition().x > cameraBounds.left && getPosition().x < cameraBounds.left + cameraBounds.width)
//	{
//		if (getPosition().y > cameraBounds.top && getPosition().y < cameraBounds.top + cameraBounds.height)
//		{
//			isVisible = true;
//			return isVisible;
//		}
//	}
//	/*******************If Not In Visible Bounds**********************/
//	isVisible = false;
//	return isVisible;
//}//--end InView()

//void Enemy::Animate()
//{
//	if (timelapse.getElapsedTime().asSeconds() > 0.15f)
//	{
//		 //Evil Mode
//		{
//			sourceRectImage.top = 0;
//
//			if (sourceRectImage.left >= 500)
//				sourceRectImage.left = 0;
//			else
//				sourceRectImage.left += 100;
//
//			setTextureRect(sourceRectImage);
//		}
//
//		//else // Good Mode 
//		//{
//		//	sourceRectImage.top = 100;
//		//	if (sourceRectImage.left >= 300)
//		//		sourceRectImage.left = 0;
//		//	else
//		//		sourceRectImage.left += 100;
//
//		//	setTextureRect(sourceRectImage);
//		//	
//		//}//--end if(isTriggered)
//
//		timelapse.restart(); //Restart Clock for Frame Count
//	}
//}
