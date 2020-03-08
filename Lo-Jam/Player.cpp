#include "Player.h"
#include <math.h>
#include "Dog.h"

//Declaration of Static Variables
#ifndef CLOCK_PLAYER
#define CLOCK_PLAYER

sf::Clock Player::delayTimer;
sf::Clock Player::playerAnimTimer;
bool Player::flipped = true;

#endif // !CLOCK_PLAYER

Player::Player(std::string ID) : Entity::Entity(ID)
{
	dog = new Dog("dog");
	dog->LoadTexture("Assets/Doggo_Idle.png");
	dog->scale(2.5, 2.5);
	dog->setPosition(200, 200);

	sourceRectImg = sf::IntRect(0, 0, 100, 100);
	setTextureRect(sourceRectImg);
	
}


Player::~Player()
{
}

void Player::Update() {
	Entity::Update();

	AnimateMovement();
	HandleHorizontalFlipping();
	MakeDogFollow();
}

void Player::AnimateMovement()
{


	(Player::playerAnimTimer.getElapsedTime().asSeconds() >= 0.5f);

		//idle
		if (magnitude == 0) {
			sourceRectImg.top = 0;

			if (sourceRectImg.left >= 300)
				sourceRectImg.left = 0;
			else {
				if (Player::playerAnimTimer.getElapsedTime().asSeconds() >= 0.5f) {
					sourceRectImg.left += 100;
					Player::playerAnimTimer.restart();
				}

			}
				
			setTextureRect(sourceRectImg);
		}

		//moving
		else if (magnitude > 0) {
			//  left/right movement 
			if (direction.x != 0.0f && std::abs(direction.x) > std::abs(direction.y)) {
				
				sourceRectImg.top = 500;
				if (sourceRectImg.left >= 500) sourceRectImg.left = 0;
				else {
					if (Player::playerAnimTimer.getElapsedTime().asSeconds() >= 0.5f) {
						sourceRectImg.left += 100;
						Player::playerAnimTimer.restart();
					}
				}

				setTextureRect(sourceRectImg);
			} 
			
			//  up movement
			if (direction.y < 0.0f && std::abs(direction.y) > std::abs(direction.x)) {
				sourceRectImg.top = 300;
				if (sourceRectImg.left >= 800) sourceRectImg.left = 0;
				else {
					if (Player::playerAnimTimer.getElapsedTime().asSeconds() >= 0.5f) {
						sourceRectImg.left += 100;
						Player::playerAnimTimer.restart();
					}
				}

				setTextureRect(sourceRectImg);
			}

			//  down movement
			else if (direction.y > 0.0f && std::abs(direction.y) > std::abs(direction.x)) {
				sourceRectImg.top = 100;
				if (sourceRectImg.left >= 800) sourceRectImg.left = 0;
				else {
					if (Player::playerAnimTimer.getElapsedTime().asSeconds() >= 0.5f) {
						sourceRectImg.left += 100;
						Player::playerAnimTimer.restart();
					}
				}


				setTextureRect(sourceRectImg);
			}
			
		}
}

void Player::HandleHorizontalFlipping()
{
	//if moving, flip image
	if (magnitude > 0) {
		if (direction.x > 0.0f && !flipped) {
			scale(-1.0f, 1.0f);
			flipped = true;
		}

		else if (direction.x < 0.0f && flipped) {
			scale(-1.0f, 1.0f);
			flipped = false;
		}

	}

}

void Player::MakeDogFollow()
{
	//if dog is further than 300 pixels away
	if (sqrt(pow((getPosition() - dog->getPosition()).x, 2) + pow((getPosition() - dog->getPosition()).y, 2)) > 300.0f) {
		if (delayTimer.getElapsedTime().asSeconds() >= 1.5f) {
			dog->MoveTo(getPosition());
			delayTimer.restart();
		}
	}
	else dog->MoveTo(dog->getPosition());

	dog->Update();
}

