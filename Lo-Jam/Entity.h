#ifndef ENTITY_H
#define ENTITY_H

#include "GameObject.h"
class Entity :
	public GameObject
{
private:
	float health;


public:
	Entity(std::string ID);
	~Entity();
	void Update() override;
};


#endif // !ENTITY_H