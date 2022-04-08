#ifndef DOG_H
#define DOG_H
#include "Entity.h"


class Dog : public Entity
{

public:

	Dog(std::string ID, Entity *owner_);
	~Dog();

	void Update();
	void Follow();

private:
	bool following;
	Entity *owner;
	sf::IntRect sourceRectImg;
	sf::Clock AnimTimer;
	sf::Clock delayTimer;
	void Animate();

};

#endif // !DOG_H
