#include "GameObject.h"



void GameObject::InteractWith(GameObject *otherObject)
{
}

GameObject::GameObject(std::string ID)
{
	m_ID = ID;
}


GameObject::~GameObject()
{
}

void GameObject::Update() {

}

bool GameObject::Collided(const GameObject* g) {
	if (sqrtf(powf((getPosition().x - g->getPosition().x), 2.0f) + powf((getPosition().y - g->getPosition().y), 2.0f)) < 100.0f) {
		return true;
	}

	return false;
}

void GameObject::LoadTexture(std::string filename) {
	if (!texture.loadFromFile(filename)) printf("Failed to load image of ", m_ID); 
	else setTexture(texture);

	setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
}
