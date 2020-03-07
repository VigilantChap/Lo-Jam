#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SFML.h"

class GameObject: public sf::Sprite
{
public:
	std::string m_ID;
	sf::Texture texture;
	//sf::Sprite sprite;

public:
	virtual void InteractWith(GameObject &otherObject);
	GameObject(std::string ID);
	~GameObject();
	
	virtual void Update();
	inline std::string getID() { return m_ID; }
	void LoadTexture(std::string filename);
};

#endif