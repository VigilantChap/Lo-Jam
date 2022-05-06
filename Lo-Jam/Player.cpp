#include "Player.h"
#include <math.h>
#include "Animator.h"




Player::Player(std::string ID) : Entity::Entity(ID)
{
	scale(3, 3);
	LoadTexture("Assets/NewPlayerSpriteSheet.png");
	
	addState(Dead_Player());

	animator = new Animator(this);
	if (!animator->Instantiate()) {
		printf("Could not instantiate %s animator.\n", ID.c_str());
		delete animator;
		animator = nullptr;
	}

	else observers.push_back(animator);

	updateCentre();
}

Player::~Player()
{
}

void Player::Update() {
	Entity::Update();

	projectiles.shrink_to_fit();
	for (int i = 0; i < projectiles.size(); i++) {
		if (projectiles[i].killMe) {
			printf("Killing projectile.\n");
			projectiles.erase(projectiles.begin() + i);
		}
		else projectiles[i].Update();
	}

}



