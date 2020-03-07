#include "Player.h"
#include <math.h>
#include "Dog.h"


Player::Player(std::string ID) : Entity::Entity(ID)
{
	dog = new Dog("dog");
	dog->LoadTexture("Assets/Doggo_Idle.png");
	dog->scale(2.5, 2.5);
	dog->setPosition(200, 200);

	
}


Player::~Player()
{
}

void Player::Update() {
	Entity::Update();

	
	static float delay = 1.5f;
	
	//if dog is further than 200 pixels away
	if (sqrt(pow((getPosition() - dog->getPosition()).x, 2) + pow((getPosition() - dog->getPosition()).y, 2)) > 300.0f) {
		if (delay <= 0.1f) {
			dog->MoveTo(getPosition());
			delay = 1.5f;
		}

		else delay -= clock.getElapsedTime().asSeconds();

		clock.restart();

	}

	else dog->MoveTo(dog->getPosition());
	
	dog->Update();
}

