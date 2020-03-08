#include "Entity.h"



Entity::Entity(std::string ID) : GameObject::GameObject(ID) {
	health = 100.0f;
	maxSpeed = 3.0f;
}



Entity::~Entity()
{
}

void Entity::MoveTo(sf::Vector2f destination_) {
	destination = destination_;
}

void Entity::Update() {
	magnitude = sqrt(pow((destination - getPosition()).x, 2) + pow((destination - getPosition()).y, 2));
	
	direction = destination - getPosition();
	direction = direction / magnitude;


	if (magnitude < 25) speed = maxSpeed / 4.0f;
	else speed = maxSpeed;

	if (magnitude > 0.05f) {
		direction.x = std::round(direction.x * speed);
		direction.y = std::round(direction.y * speed);
		move(direction);
	}
	else
	{
		magnitude = 0.0f;
	}
}

bool Entity::Collided(const GameObject *g) {
	if (std::abs(sqrt((getPosition().x - g->getPosition().x) + (getPosition().y - g->getPosition().y))) < 1) {
		return true;
	}

	return false;
}
