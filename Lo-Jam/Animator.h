#ifndef ANIMATOR_H
#define ANIMATOR_H
#include "SFML.h"
#include "IObserver.h"

#define frameWidth 32
#define textureWidth AnimatedEntity->texture.getSize().x

class Animator : public IObserver
{
private:
	sf::Image* TextureImage;
	sf::IntRect animFrame;
	static sf::Clock AnimTimer;

	struct Animation {
		int up, down, left, right;
		int frameCount = 0;
	} idleAnim, walkAnim, attackAnim, projectileAnim;

	class Entity* AnimatedEntity;

	std::map<std::string, Animation&> animations;
	Animation currentAnimation;

	void setAnimCoords();
	void calculateFrames(Animation &n);	
	bool isValidFrame(sf::Vector2i framePos);

	bool isUp, isLeft, isRight, isDown;


public:

	Animator(Entity* animated_entity);
	~Animator();

	bool Instantiate();

	void ObservableEvent(GameEvent& e) override;
	void Animate();
};

#endif // !ANIMATOR_H