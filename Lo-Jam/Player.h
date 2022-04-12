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

#ifndef DEAD_PLAYER_H
#define DEAD_PLAYER_H
#include "Script.h"

struct Dead_Player : public Script
{
public:

	Dead_Player() {}

	const std::string getName() override { return "dead"; }

	void Update() override {

	}

	~Dead_Player() {}
};
#endif // !DEAD_PLAYER_H
