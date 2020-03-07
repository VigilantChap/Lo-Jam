#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity
{
public:
	Player(std::string ID);
	~Player();
};


#endif // !PLAYER_H