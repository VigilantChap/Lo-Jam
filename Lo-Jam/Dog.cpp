#include "Dog.h"

Dog::Dog(std::string ID) : Entity::Entity(ID)
{
	maxSpeed = 1.5f;
	lastPosition = getPosition();
}


Dog::~Dog()
{
}

void Dog::Update() {
	Entity::Update();
	static bool flipped = true;

	if (lastPosition.x - getPosition().x > 0 && !flipped) {
		scale(-1.0f, 1.0f);
		flipped = true;
	}

	else if (lastPosition.x - getPosition().x < 0 && flipped) {
		scale(-1.0f, 1.0f);
		flipped = false;
	}

	lastPosition = getPosition();
}
