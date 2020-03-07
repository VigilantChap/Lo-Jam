#include "Entity.h"



Entity::Entity(std::string ID) : GameObject::GameObject(ID) {
	health = 100.0f;
}



Entity::~Entity()
{
}

void Entity::MoveTo(sf::Vector2f destination_) {
	destination = destination_;
}

void Entity::Update() {
	float distance = sqrt(pow((destination - getPosition()).x, 2) + pow((destination - getPosition()).y, 2));
	if (distance > 0.1f) {
		move((destination - getPosition()) * 0.001f);
	}
}
