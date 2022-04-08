#include "Entity.h"



Entity::Entity(std::string ID) : GameObject::GameObject(ID) {
	health = 100.0f;
	maxHealth = 100.0f;
	maxSpeed = 30.0f;

	GoingToDestination = false;
	Idling = true;
}



Entity::~Entity()
{
}

void Entity::MoveTo(sf::Vector2f destination_) {
	destination = destination_;
	Idling = false;
	GoingToDestination = true;
}

void Entity::HandleState() {

	if (GoingToDestination) {
		magnitude = sqrtf(powf((destination - getPosition()).x, 2.0f) + powf((destination - getPosition()).y, 2.0f));

		direction = destination - getPosition();
		direction = direction / magnitude;


		if (magnitude < 25) speed = maxSpeed / 4.0f;
		else speed = maxSpeed;

		if (magnitude > 10) {
			direction.x = std::round(direction.x * speed);
			direction.y = std::round(direction.y * speed);
			move(direction);
		}
		else
		{
			magnitude = 0.0f;
			GoingToDestination = false;
			Idling = true;
		}
	}

	if (Idling) {

	}

	if (health <= 0) GoingToDestination = false;
}

void Entity::Update() {

	HandleState();
}

bool Entity::Collided(const GameObject *g) {
	if (sqrtf(powf((getPosition().x - g->getPosition().x), 2.0f) + powf((getPosition().y - g->getPosition().y), 2.0f)) < 100.0f) {
		return true;
	}

	return false;
}
