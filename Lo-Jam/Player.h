#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity
{
public:
	Player(std::string ID);
	~Player();

	void Update();
	inline const Entity* getDog() { if(dog != nullptr) return dog; }

private:
	class Entity* dog;
	sf::Clock clock;
	sf::IntRect sourceRectImg;
};


#endif // !PLAYER_H