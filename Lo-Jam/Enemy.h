#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
#include <random>

class Enemy : public Entity
{
	/*Variables*/
public:
	sf::Clock timelapse;
	std::default_random_engine pgenerator;
	bool isTriggered;

private:
	sf::IntRect sourceRectImage;
	sf::Vector2<float> playerPosition;
	bool isVisible;
	class Camera *camera;

	/*Methods*/
public:
	Enemy(std::string ID);
	~Enemy(); 

	void Update();
	void SetPlayerPosition(sf::Vector2<float>);
	void StartPatrolMovementTowardsTarget();
	bool InView(Camera &camera_);

private:
	void Animate();

};


#endif // !ENEMY_H
