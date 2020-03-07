#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity
{
public:
	static sf::Clock delayTimer;
	static sf::Clock playerAnimTimer;
	Player(std::string ID);
	~Player();

	void Update();
	inline const Entity* getDog() { if(dog != nullptr) return dog; }

private:
	class Entity* dog;
	sf::IntRect sourceRectImg;

};


#endif // !PLAYER_H