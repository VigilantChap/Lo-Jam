#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SFML.h"

class GameObject: public sf::Sprite
{
public:
	std::string m_ID;
	sf::Texture texture;

public:
	virtual void InteractWith(GameObject &otherObject);
	GameObject(std::string ID);
	~GameObject();
	
	virtual void Update();
	inline std::string getID() { return m_ID; }
	void LoadTexture(std::string filename);
	inline void updateCentre() { setOrigin(getTextureRect().width / 2.0f, getTextureRect().height / 2.0f); }
};

#endif