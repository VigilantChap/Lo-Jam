#include "Player.h"
#include <math.h>


Player::Player(std::string ID) : Entity::Entity(ID)
{

}


Player::~Player()
{
}

void Player::MoveTo(sf::Vector2f destination_) {
	destination = destination_;
}

void Player::Update() {
	float distance = sqrt(pow((destination - getPosition()).x, 2) + pow((destination - getPosition()).y, 2));
	if (distance > 0.1f) {
		move((destination - getPosition()) * 0.001f);
	}
}

