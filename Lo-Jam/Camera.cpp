#include "Camera.h"
#include "GameObject.h"
#include <iostream>



Camera::Camera(sf::RenderWindow * window_): window(window_)
{
	view.setCenter(sf::Vector2f(1024.f, 1024.f));
	updateViewSize();

	
}

bool Camera::Initialize()
{
	return true;
}

void Camera::Destroy()
{
}

void Camera::HandleEvents(sf::Event event)
{
	if (event.type == sf::Event::Resized)
	{
		updateViewSize();
	}
	
	
}

void Camera::Update()
{
	if (followTarget) {
		view.setCenter(followTarget->getPosition());
		SetAsMainView();
	}
}

void Camera::Render()
{
}

void Camera::SetAsMainView()
{
	window->setView(view);
}



void Camera::SetFollowTarget(GameObject *target)
{
	followTarget = target;
}
