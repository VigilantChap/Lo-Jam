#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "MusicPlayer.h"

class Player : public Entity
{

	struct Projectile : public GameObject {
		sf::Vector2f fireDirection;
		sf::Clock lifetime;
		bool killMe;

		Projectile(sf::Vector2f spawnLocation, sf::Vector2f ptarget, sf::Texture &t) : GameObject("projectile") {
			this->setTexture(t);
			this->setTextureRect(sf::IntRect(32, 288, 32, 32));
			this->scale(6, 6);
			killMe = false;
			const auto mag = sqrt(powf((ptarget - spawnLocation).x, 2.0f) + powf((ptarget - spawnLocation).y, 2.0f));
			fireDirection = (ptarget - spawnLocation) / mag;
			setPosition(spawnLocation);
			lifetime.restart();
		}

		void Update() override {
			if (!killMe) {
				GameObject::Update();
				this->move(fireDirection.x * 20, fireDirection.y * 20);
			}

			if (lifetime.getElapsedTime().asSeconds() >= 3.5f && !killMe) killMe = true;
			
		}

		void OnTriggerEnter(GameObject* g) override {
			if (g->getID().compare("enemy") == 0) {
				dynamic_cast<Entity*>(g)->takeDamage(50);
			}
		}

		~Projectile() {

		}

	};


public:

	Player(std::string ID);
	~Player();

	void Update();

	std::vector<Projectile> projectiles;
	
	inline void fire(const sf::Vector2f & position) { 
		projectiles.push_back(Projectile(this->getPosition(), position, texture));
		MusicPlayer::PlayPewSound();
		printf("Fire!\n");
	}

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
