#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SFML.h"
#include "Script.h"




class GameObject: public sf::Sprite
{
protected:
	std::string m_ID;
	sf::Texture texture;



	//std::list<Script*> scripts;

public:
	virtual void InteractWith(GameObject *otherObject);
	GameObject(std::string ID);
	~GameObject();
	
	virtual void Update();

	//void AddScript(Script* script) { scripts.push_back(script); }

	inline std::string getID() { return m_ID; }
	void LoadTexture(std::string filename);
	inline void updateCentre() { setOrigin(getTextureRect().width / 2.0f, getTextureRect().height / 2.0f); }
	bool Collided(const GameObject* g);
};

#endif