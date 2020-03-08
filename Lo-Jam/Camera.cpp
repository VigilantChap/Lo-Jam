#include "Camera.h"
#include "GameObject.h"
#include <iostream>
#include <cmath>



Camera::Camera(sf::RenderWindow * window_): window(window_)
{
	view.setCenter(sf::Vector2f(1024.f, 1024.f));
	updateViewSize();
	frame = 60;
	
}

bool Camera::Initialize()
{
	return true;
}

void Camera::Destroy()
{
	delete followTarget;
	followTarget = nullptr;
	
	window->close();
	delete window;
	window = nullptr;


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
		//TODO: Remove flickering by rounding values to int value.
		
			imageBuffer = followTarget->getPosition();
			
		view.setCenter(sf::Vector2<float>(std::round(imageBuffer.x), std::round(imageBuffer.y)));
		SetAsMainView();
	}
	frame++;
}

void Camera::Render()
{
}

void Camera::SetAsMainView()
{
	window->setView(view);
}

sf::View Camera::GetView()
{
	return view;
}





void Camera::SetFollowTarget(GameObject *target)
{
	followTarget = target;
}
