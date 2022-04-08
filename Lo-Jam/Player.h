#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity
{
	friend class Dog;

public:


	static bool flipped;
	Player(std::string ID);
	~Player();

	void Update();
	inline const Entity* getDog() { return dog; }
	//sf::Vector2<float> destination;

private:
	class Entity* dog;
	sf::IntRect sourceRectImg;
	static sf::Clock playerAnimTimer;
	/*static sf::Clock delayTimer;*/

	void AnimateMovement();
	void HandleHorizontalFlipping();
	void MakeDogFollow();
	bool isUp, isLeftRight, isDown;
};


#endif // !PLAYER_H