#include "Player.h"
#include <math.h>
#include "Dog.h"
#include "Animator.h"




Player::Player(std::string ID) : Entity::Entity(ID)
{
	dog = new Dog("dog", this);
	dog->LoadTexture("Assets/DoggoSpriteSheet.png");
	dog->scale(2.5, 2.5);
	dog->updateCentre();
	dog->setPosition(200, 200);

	//sourceRectImg = sf::IntRect(0, 0, 100, 100);
	//setTextureRect(sourceRectImg);
	//LoadTexture("Assets/PlayerSpriteSheet.png"); //old sprite
	scale(3, 3);
	LoadTexture("Assets/NewPlayerSpriteSheet.png");
	
	addState(Dead_Player());

	animator = new Animator(this);
	observers.push_back(animator);
	updateCentre();
}

Player::~Player()
{
	delete dog;
	dog = nullptr;
}

void Player::Update() {
	Entity::Update();

	animator->Animate();

	projectiles.shrink_to_fit();
	for (int i = 0; i < projectiles.size(); i++) {
		if (projectiles[i].killMe) {
			printf("Killing projectile.\n");
			projectiles.erase(projectiles.begin() + i);
		}
		else projectiles[i].Update();
	}


	dog->Update();
}



