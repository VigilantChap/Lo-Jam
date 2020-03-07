#ifndef SCENE_H
#define SCENE_H
#include "SFML.h"

class Scene {
public:
	virtual bool Initialize() = 0;
	virtual void Destroy() = 0;
	virtual void HandleEvents(sf::Event event) const = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};


#endif // !SCENE_H

