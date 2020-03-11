#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity
{
public:
	static sf::Clock delayTimer;
	static sf::Clock playerAnimTimer;
	static bool flipped;
	Player(std::string ID);
	~Player();

	void Update();
	inline const Entity* getDog() { if(dog != nullptr) return dog; }
	sf::Vector2<float> destination;

private:
	class Entity* dog;
	sf::IntRect sourceRectImg;

	void AnimateMovement();
	void HandleHorizontalFlipping();
	void MakeDogFollow();
	bool isUp, isLeftRight, isDown;
};


#endif // !PLAYER_H