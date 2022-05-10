#ifndef SCENE_H
#define SCENE_H
#include "SFML.h"


class Scene {
public:
	virtual bool Initialize() = 0;
	virtual void Destroy() = 0;
	virtual void HandleEvents(const sf::Event event) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	bool changeScene = false;
	bool quit = false;
	std::string sceneName;
};


#endif // !SCENE_H

