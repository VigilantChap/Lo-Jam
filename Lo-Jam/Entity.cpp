#include "Entity.h"



Entity::Entity(std::string ID) : GameObject::GameObject(ID) {
	health = 100.0f;
}



Entity::~Entity()
{
}


void Entity::Update() {

}
