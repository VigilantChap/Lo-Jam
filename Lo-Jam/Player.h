#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity
{
public:
	Player(std::string ID);
	~Player();

	void Update();
	void MoveTo(sf::Vector2f destination_);

private:
	sf::Vector2f destination;
};


#endif // !PLAYER_H