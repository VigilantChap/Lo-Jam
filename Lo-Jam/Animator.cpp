#include "Animator.h"
#include "Entity.h"

sf::Clock Animator::AnimTimer;

void Animator::ObservableEvent(GameEvent& e)
{
	const auto sourceID = e.source->getID();

	if (e.type == GameEvent::SateChange) {
		std::string s = dynamic_cast<Entity*>(e.source)->currentState->getName();
		if (animations.find(s) != animations.end()) {
			currentAnimation = animations.find(s)->second;
			/*printf("Changing %s animator state.\n", sourceID.c_str());*/
		}
	}
}


void Animator::setAnimCoords()
{
	idleAnim.down = idleAnim.up = idleAnim.left = idleAnim.right = frameWidth;
	idleAnim.up += frameWidth;
	idleAnim.right += (frameWidth * 2);
	idleAnim.left += (frameWidth * 3);

	walkAnim.down = walkAnim.up = walkAnim.left = walkAnim.right = 160;
	walkAnim.up += frameWidth;
	walkAnim.right += (frameWidth * 2);
	walkAnim.left += (frameWidth * 3);

	attackAnim.down = attackAnim.up = attackAnim.left = attackAnim.right = 320;
	attackAnim.up += frameWidth;
	attackAnim.right += (frameWidth * 2);
	attackAnim.left += (frameWidth * 3);

	projectileAnim.down = projectileAnim.up  = projectileAnim.right = projectileAnim.left = 288;

	animations.emplace("idle", idleAnim);
	animations.emplace("moving", walkAnim);
	animations.emplace("attacking", attackAnim);
	animations.emplace("projectile", projectileAnim);

	for (auto anim : animations) {
		calculateFrames(anim.second);
		printf("%s frameCount: %i \n", anim.first.c_str(), anim.second.frameCount);
	}
}

void Animator::calculateFrames(Animation& n) {
	sf::Vector2i frameCoords(frameWidth, n.down);

	while (true) {
		if (isValidFrame(frameCoords)) {
			frameCoords.x += frameWidth;
			if (frameCoords.x > textureWidth) break;
			n.frameCount++;
		}

		else break;
	}
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

}

Animator::~Animator()
{
}

bool Animator::Instantiate()
{	
	TextureImage = new sf::Image();
	if (!TextureImage->loadFromFile(AnimatedEntity->textureFilePath)) {
		printf("Animator's entity has no texture\n");
		return false;
	}

	isUp = false;
	isDown = true;
	isLeft = false;
	isRight = false;
	animFrame = sf::IntRect(32, 32, 32, 32);
	AnimatedEntity->setTextureRect(animFrame);
	setAnimCoords();


	return true;
}

void Animator::Animate()
{

	//  left/right movement 
	if (AnimatedEntity->direction.x != 0.0f && std::abs(AnimatedEntity->direction.x) > std::abs(AnimatedEntity->direction.y)) {

		//right
		if (AnimatedEntity->direction.x > 0) {
			animFrame.top = currentAnimation.right;
		}

		//left
		else if (AnimatedEntity->direction.x < 0) {
			animFrame.top = currentAnimation.left;
		}
	}

	//  up movement
	if (AnimatedEntity->direction.y < 0.0f && std::abs(AnimatedEntity->direction.y) > std::abs(AnimatedEntity->direction.x)) {

		animFrame.top = currentAnimation.up;
	}

	//  down movement
	else if (AnimatedEntity->direction.y > 0.0f && std::abs(AnimatedEntity->direction.y) > std::abs(AnimatedEntity->direction.x)) {

		animFrame.top = currentAnimation.down;
	}
	

	if (AnimTimer.getElapsedTime().asSeconds() >= 0.15f) {
		//animFrame.left = (animFrame.left % (frameWidth * currentAnimation.frameCount)) + frameWidth;
		animFrame.left += frameWidth;
		if (animFrame.left > (frameWidth * currentAnimation.frameCount)) animFrame.left = frameWidth;
		AnimTimer.restart();
	}

	AnimatedEntity->setTextureRect(animFrame);
}

//----- OLD ANIMATE
//{
//	//idle
//	if (AnimatedEntity->checkState("idle")) {
//
//		//facing down
//		if (isDown) animFrame.top = idleAnim.down; //y = 32
//		//facing up
//		if (isUp) animFrame.top = idleAnim.up; //y = 64
//		//facing left or right
//		if (isRight) animFrame.top = idleAnim.right; //y = 96
//		if (isLeft) animFrame.top = idleAnim.left; //y = 128
//
//
//		if (animFrame.left >= 159)
//			animFrame.left = frameWidth; // x = 32
//	}
//
//	//moving
//	else if (AnimatedEntity->checkState("moving")) {
//		//  left/right movement 
//		if (AnimatedEntity->direction.x != 0.0f && std::abs(AnimatedEntity->direction.x) > std::abs(AnimatedEntity->direction.y)) {
//			isUp = false;
//			isDown = false;
//
//			//right
//			if (AnimatedEntity->direction.x > 0) {
//				isRight = true;
//				isLeft = false;
//				animFrame.top = walkAnim.right;
//			}
//
//			//left
//			else if (AnimatedEntity->direction.x < 0) {
//				isLeft = true;
//				isRight = false;
//				animFrame.top = walkAnim.left;
//			}
//		}
//
//		//  up movement
//		if (AnimatedEntity->direction.y < 0.0f && std::abs(AnimatedEntity->direction.y) > std::abs(AnimatedEntity->direction.x)) {
//			isUp = true;
//			isDown = false;
//			isRight = isLeft = false;
//			animFrame.top = walkAnim.up;
//		}
//
//		//  down movement
//		else if (AnimatedEntity->direction.y > 0.0f && std::abs(AnimatedEntity->direction.y) > std::abs(AnimatedEntity->direction.x)) {
//			isUp = false;
//			isDown = true;
//			isRight = isLeft = false;
//			animFrame.top = walkAnim.down;
//		}
//
//
//
//		if (animFrame.left >= textureWidth) animFrame.left = frameWidth;
//	}
//
//	if (AnimTimer.getElapsedTime().asSeconds() >= 0.15f) {
//		animFrame.left += frameWidth;
//		AnimTimer.restart();
//	}
//
//	AnimatedEntity->setTextureRect(animFrame);
//}


