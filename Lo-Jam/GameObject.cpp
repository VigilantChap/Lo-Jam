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
	//for (Script* script : scripts) {
	//	script->Update();
	//}

	updateCentre();
}

bool GameObject::Collided(const GameObject* g) {

	const sf::FloatRect collider1 = this->getGlobalBounds();
	const sf::FloatRect collider2 = g->getGlobalBounds();

	if (collider1.intersects(collider2)) {
		return true;
	}

	return false;
}

void GameObject::LoadTexture(std::string filename) {
	if (!texture.loadFromFile(filename)) printf("Failed to load image of %s", m_ID.c_str()); 
	else setTexture(texture);
	
	updateCentre();
	textureFilePath = filename;
}
