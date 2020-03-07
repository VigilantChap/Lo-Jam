#include "GameObject.h"



void GameObject::InteractWith(GameObject & otherObject)
{
}

GameObject::GameObject(std::string ID)
{
	m_ID = ID;
}


GameObject::~GameObject()
{
}

//void GameObject::draw(sf::RenderTarget & target, sf::RenderStates states) const
//{
//}

//
//void GameObject::draw(sf::RenderTarget & target)
//{
//	setPosition(getPosition());
//	target.draw(sprite);
//}

void GameObject::Update() {

}

void GameObject::LoadTexture(std::string filename) {
	if (!texture.loadFromFile(filename)) printf("Failed to load image of ", m_ID); 
	else setTexture(texture); 	

	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}
