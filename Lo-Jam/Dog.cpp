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
	Animate();


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
