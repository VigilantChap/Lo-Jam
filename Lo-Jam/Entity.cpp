#include "Entity.h"



Entity::Entity(std::string ID) : GameObject::GameObject(ID) {
	health = 100.0f;
	speed = 3.0f;
}



Entity::~Entity()
{
}

void Entity::MoveTo(sf::Vector2f destination_) {
	destination = destination_;
}

void Entity::Update() {
	float magnitude = sqrt(pow((destination - getPosition()).x, 2) + pow((destination - getPosition()).y, 2));
	sf::Vector2f direction;	
	direction = destination - getPosition();
	direction = direction / magnitude;


	if (magnitude < 25) speed = 0.75f;
	else speed = 3;

	if (magnitude > 0.5f) {
		direction.x = std::round(direction.x * speed);
		direction.y = std::round(direction.y * speed);
		move(direction);
	}
	else
	{
		magnitude = 0.0f;
	}
}
