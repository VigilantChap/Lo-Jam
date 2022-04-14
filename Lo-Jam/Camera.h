#ifndef CAMERA_H
#define CAMERA_H
#include "SFML.h"

class Camera {
private:
	class GameObject* followTarget;
	sf::View view;
	sf::RenderWindow* window;
	sf::Vector2f imageBuffer;
	inline void updateViewSize() { view.setSize(window->getView().getSize()); SetAsMainView(); view.zoom(4); }

public:
	Camera(sf::RenderWindow * window_);
	~Camera();
	void SetFollowTarget(GameObject *target);
	void HandleEvents(sf::Event event);
	void Update();
	void Render();
	void SetAsMainView();
	sf::View GetView();
	
};







#endif // !CAMERA_H

