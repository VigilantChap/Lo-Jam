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
	
	inline void doThing(int x) { 
		if (x == 1) {
			printf("Player says: I'm doing Thing1\n");
			Notify(GameEvent(GameEvent::Thing1).makeWithSource(this));
		}

		else if (x == 2) {
			printf("Player says: I'm doing Thing2\n");
			Notify(GameEvent(GameEvent::Thing2).makeWithSource(this));
		}

	}

private:
	class Entity* dog;
	sf::IntRect sourceRectImg;
	static sf::Clock playerAnimTimer;

	void AnimateMovement();
	void HandleHorizontalFlipping();
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
