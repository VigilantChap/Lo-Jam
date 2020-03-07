#include "Dog.h"

Dog::Dog(std::string ID) : Entity::Entity(ID)
{
	maxSpeed = 1.5f;

	
}


Dog::~Dog()
{
}

void Dog::Update() {
	Entity::Update();
	static bool flipped = false;

	//if moving, flip image
	if (magnitude > 0) {
		if (direction.x > 0.0f && !flipped) {
			scale(-1.0f, 1.0f);
			flipped = true;
		}

		else if (direction.x < 0.0f && flipped) {
			scale(-1.0f, 1.0f);
			flipped = false;
		}

	}
}
