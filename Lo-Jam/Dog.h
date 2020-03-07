#ifndef DOG_H
#define DOG_H
#include "Entity.h"


class Dog : public Entity
{
public:
	Dog(std::string ID);
	~Dog();

	void Update();

private:
	sf::Vector2f lastPosition;
};

#endif // !DOG_H
