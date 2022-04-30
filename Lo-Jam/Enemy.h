#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
#include <random>

class Enemy : public Entity
{
	/*Variables*/
public:	
	bool isTriggered;

private:
	sf::IntRect sourceRectImage;
	sf::Clock timelapse;
	sf::Clock AIdelay;
	sf::Vector2f playerPosition;
	static std::default_random_engine pgenerator;
	bool isVisible;

	class Animator* animator;

	/*Methods*/
public:
	Enemy(std::string ID);
	~Enemy(); 

	void Update();
	void SetPlayerPosition(sf::Vector2f position);
	void StartPatrolMovementTowardsTarget();
	

private:
	void Animate();
	void HandleState();
};


#endif // !ENEMY_H
