#include "Dog.h"

Dog::Dog(std::string ID, Entity *owner_) : Entity::Entity(ID), owner(owner_)
{
	maxSpeed = 15.0f; 
	sourceRectImg = sf::IntRect(0, 0, 100, 100);
	setTextureRect(sourceRectImg);
	following = true;
}


Dog::~Dog()
{
}

void Dog::Update() {
	Entity::Update();
	
	if (following) Follow();

	Animate();


}

void Dog::Follow() {
	if (sqrt(pow((owner->getPosition() - getPosition()).x, 2) + pow((owner->getPosition() - getPosition()).y, 2)) > 300.0f) {
		if (delayTimer.getElapsedTime().asSeconds() >= 1.5f) {
			MoveTo(owner->getPosition());
			delayTimer.restart();
		}
	}
}

void Dog::Animate()
{
	static bool flipped = false;
	//idle
	if (Idling) {
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
	else {
		//  left/right movement 
		
			sourceRectImg.top = 100;
			if (sourceRectImg.left >= 400)
			{
				sourceRectImg.left = 0;
			}
			else {
				if (AnimTimer.getElapsedTime().asSeconds() >= 0.175f) {
					sourceRectImg.left += 100;
					AnimTimer.restart();
				}
				
					maxSpeed = 15;
				
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
