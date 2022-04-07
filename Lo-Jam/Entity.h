#ifndef ENTITY_H
#define ENTITY_H

#include "GameObject.h"
class Entity :
	public GameObject
{
protected:
	float health;
	float maxHealth;
	sf::Vector2f destination;
	float speed;
	float maxSpeed;
	float magnitude;
	sf::Vector2f direction;

public:
	Entity(std::string ID);
	~Entity();
	void Update() override;
	void MoveTo(sf::Vector2f destination_);
	inline void setMaxSpeed(float speed_) { speed = speed_; }
	inline float getHealth() { return health; }

	inline void takeDamage(float value) { 
		if (health >= value) {
			health -= value;
		}

		else health = 0;	
	}

	inline void heal(float value) {
		if (health <= maxHealth - value) {
			health += value;
		}

		else health = maxHealth;
		printf("You Healed!\n");
	}

	bool Collided(const GameObject *g);
};


#endif // !ENTITY_H