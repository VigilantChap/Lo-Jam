#include "Player.h"
#include <math.h>
#include "Dog.h"


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
	static sf::Clock delayTimer;
	static sf::Clock playerAnimTimer;
	
	if (playerAnimTimer.getElapsedTime().asSeconds() > 1.0f) {
		if (sourceRectImg.left >= 300)
			sourceRectImg.left = 0;
		else
			sourceRectImg.left += 100;

		setTextureRect(sourceRectImg);
		playerAnimTimer.restart();
	}
	
	//if dog is further than 200 pixels away
	if (sqrt(pow((getPosition() - dog->getPosition()).x, 2) + pow((getPosition() - dog->getPosition()).y, 2)) > 300.0f) {
		if (delayTimer.getElapsedTime().asSeconds() >= 1.5f) {
			dog->MoveTo(getPosition());
			delayTimer.restart();
		}
	}

	else dog->MoveTo(dog->getPosition());
	
	dog->Update();
}

