#ifndef ENTITY_H
#define ENTITY_H

#include "GameObject.h"
class Entity :
	public GameObject
{
private:
	float health;
	sf::Vector2f destination;

public:
	Entity(std::string ID);
	~Entity();
	void Update() override;
	void MoveTo(sf::Vector2f destination_);
};


#endif // !ENTITY_H