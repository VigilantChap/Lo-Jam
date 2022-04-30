#include "Animator.h"
#include "Entity.h"

sf::Clock Animator::AnimTimer;

void Animator::ObservableEvent(GameEvent& e)
{
	const auto sourceID = e.source->getID();
			
	//if (e.type == GameEvent::Thing1) {
	//		if (sourceID.compare(AnimatedEntity->getID()) == 0) {
	//				printf("Animator is responding to changeState event.\n");
	//				EntityState = AnimatedEntity->currentState->getName();
	//		}
	//}
}


void Animator::setAnimCoords()
{
	idleCoords.down = idleCoords.up = idleCoords.left = idleCoords.right = 32;
	idleCoords.up += 32;
	idleCoords.right += (32 * 2);
	idleCoords.left += (32 * 3);

	walkCoords.down = walkCoords.up = walkCoords.left = walkCoords.right = 160;
	walkCoords.up += 32;
	walkCoords.right += (32 * 2);
	walkCoords.left += (32 * 3);

	attackCoords.down = attackCoords.up = attackCoords.left = attackCoords.right = 320;
	attackCoords.up += 32;
	attackCoords.right += (32 * 2);
	attackCoords.left += (32 * 3);

	projectileCoords.down = projectileCoords.up  = projectileCoords.right = projectileCoords.left = 288;

	calculateFrames(idleCoords);
	calculateFrames(walkCoords);
	calculateFrames(attackCoords);
	calculateFrames(projectileCoords);
}

void Animator::calculateFrames(animCoords& n) {
	sf::Vector2i frameCoords(frameWidth, n.down);

	while (true) {
		if (isValidFrame(frameCoords)) {
			frameCoords.x += frameWidth;
			if (frameCoords.x > textureWidth) break;
			n.frameCount++;
		}

		else break;
	}

	printf("anim frameCount: %i \n", n.frameCount);
}


bool Animator::isValidFrame(sf::Vector2i framePos)
{
	for (int i = 0; i < frameWidth; i++) {
		for (int j = 0; j < frameWidth; j++) {
			if (TextureImage->getPixel(framePos.x + j, framePos.y + i).a != 0) return true;
		}
	}

	return false;
}
Animator::Animator(Entity* p_animated_entity) : AnimatedEntity(p_animated_entity)
{
	TextureImage = new sf::Image();
	if(!TextureImage->loadFromFile(AnimatedEntity->textureFilePath)) printf("animator's entity has no texture\n");

	isUp = false;
	isDown = true;
	isLeft = false;
	isRight = false;
	animFrame = sf::IntRect(32, 32, 32, 32);
	AnimatedEntity->setTextureRect(animFrame);
	setAnimCoords();
}

Animator::~Animator()
{
}

void Animator::Animate()
{
	//idle
	if (AnimatedEntity->checkState("idle")) {

		//facing down
		if (isDown) animFrame.top = idleCoords.down; //y = 32
		//facing up
		if (isUp) animFrame.top = idleCoords.up; //y = 64
		//facing left or right
		if (isRight) animFrame.top = idleCoords.right; //y = 96
		if (isLeft) animFrame.top = idleCoords.left; //y = 128


		if (animFrame.left >= 159)
			animFrame.left = frameWidth; // x = 32
	}

	//moving
	else if (AnimatedEntity->checkState("moving")) {
		//  left/right movement 
		if (AnimatedEntity->direction.x != 0.0f && std::abs(AnimatedEntity->direction.x) > std::abs(AnimatedEntity->direction.y)) {
			isUp = false;
			isDown = false;

			//right
			if (AnimatedEntity->direction.x > 0) {
				isRight = true;
				isLeft = false;
				animFrame.top = walkCoords.right;
			}

			//left
			else if (AnimatedEntity->direction.x < 0) {
				isLeft = true;
				isRight = false;
				animFrame.top = walkCoords.left;
			}
		}

		//  up movement
		if (AnimatedEntity->direction.y < 0.0f && std::abs(AnimatedEntity->direction.y) > std::abs(AnimatedEntity->direction.x)) {
			isUp = true;
			isDown = false;
			isRight = isLeft = false;
			animFrame.top = walkCoords.up;
		}

		//  down movement
		else if (AnimatedEntity->direction.y > 0.0f && std::abs(AnimatedEntity->direction.y) > std::abs(AnimatedEntity->direction.x)) {
			isUp = false;
			isDown = true;
			isRight = isLeft = false;
			animFrame.top = walkCoords.down;
		}



		if (animFrame.left >= textureWidth) animFrame.left = frameWidth;
	}

	if (AnimTimer.getElapsedTime().asSeconds() >= 0.15f) {
		animFrame.left += frameWidth;
		AnimTimer.restart();
	}

	AnimatedEntity->setTextureRect(animFrame);
}


