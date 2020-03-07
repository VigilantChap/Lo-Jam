#ifndef CAMERA_H
#define CAMERA_H
#include "SFML.h"

class Camera {
private:
	class GameObject* followTarget;
	sf::View view;
	sf::RenderWindow* window;
	inline void updateViewSize() { view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y)); SetAsMainView(); view.zoom(4); }

public:
	Camera(sf::RenderWindow * window_);
	void SetFollowTarget(GameObject *target);
	bool Initialize();
	void Destroy();
	void HandleEvents(sf::Event event);
	void Update();
	void Render();
	void SetAsMainView();
	
};







#endif // !CAMERA_H

