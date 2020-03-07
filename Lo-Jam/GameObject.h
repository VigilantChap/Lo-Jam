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
	
	// Inherited via Drawable
	//virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	virtual void Update();
	//void draw(sf::RenderTarget & target);
	inline std::string getID() { return m_ID; }
	void LoadTexture(std::string filename);
};

#endif