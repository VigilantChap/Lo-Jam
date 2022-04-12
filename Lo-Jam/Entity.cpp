#include "Entity.h"

Entity::Entity(std::string ID) : GameObject::GameObject(ID) {
	health = 100.0f;
	maxHealth = 100.0f;
	maxSpeed = 30.0f;

	states = std::map<std::string, Script*>();

	addState(Moving_Entity(this));
	addState(Idle_Entity());
	setState("idle");
}



Entity::~Entity()
{
	delete currentState;
	currentState = nullptr;
}

void Entity::MoveTo(sf::Vector2f destination_) {
	destination = destination_;
	setState("moving");
}

void Entity::HandleState() {

	if (health <= 0) setState("idle");
	
	updateState;
	
	if (!currentState) 
	{
		setState("idle");
	}
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
