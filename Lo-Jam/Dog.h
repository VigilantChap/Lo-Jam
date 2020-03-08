#ifndef DOG_H
#define DOG_H
#include "Entity.h"


class Dog : public Entity
{
public:
	sf::Clock AnimTimer;
	Dog(std::string ID);
	~Dog();

	void Update();

private:
	sf::IntRect sourceRectImg;

	void AnimateMovement();
};

#endif // !DOG_H
