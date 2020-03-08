#include "Dog.h"

Dog::Dog(std::string ID) : Entity::Entity(ID)
{
	maxSpeed = 15.0f; 
	sourceRectImg = sf::IntRect(0, 0, 100, 100);
	setTextureRect(sourceRectImg);

}


Dog::~Dog()
{
}

void Dog::Update() {
	Entity::Update();
	AnimateMovement();
}

void Dog::AnimateMovement()
{
	static bool flipped = false;
	//idle
	if (magnitude == 0) {
		sourceRectImg.top = 0;

		if (sourceRectImg.left >= 1000)
			sourceRectImg.left = 0;
		else {
			if (AnimTimer.getElapsedTime().asSeconds() >= 0.5f) {
				sourceRectImg.left += 100;
				AnimTimer.restart();
			}

		}

		setTextureRect(sourceRectImg);
	}

	//moving
	else if (magnitude > 0) {
		//  left/right movement 
		
			sourceRectImg.top = 100;
			if (sourceRectImg.left >= 500) sourceRectImg.left = 0;
			else {
				if (AnimTimer.getElapsedTime().asSeconds() >= 0.5f) {
					sourceRectImg.left += 100;
					AnimTimer.restart();
				}
				if (sourceRectImg.left >= 300)
				{
					maxSpeed = 0.0f;
				}
				else
				{
					maxSpeed = 15.0f;
				}
			}

			setTextureRect(sourceRectImg);

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
