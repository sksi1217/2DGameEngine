#include "Camera.h"
#include <iostream>

Camera::Camera()
{
}

Camera::Camera(float newWidth, float newHeight)
	: position(glm::vec2(0.0f)), zoom(1.0f)
{
	projectionMatrix = glm::ortho(0.0f, newWidth * 2, newHeight * 2, 0.0f, -1.0f, 1.0f);
	viewMatrix = glm::mat4(1.0f);
}

void Camera::setPosition(const glm::vec2 &newPosition)
{
	position = newPosition;
	update();
}

void Camera::setZoom(float newZoom)
{
	zoom = newZoom;
	update();
}

void Camera::resize(float newWidth, float newHeight)
{
	projectionMatrix = glm::ortho(0.0f, newWidth * 2, newHeight * 2, 0.0f, -1.0f, 1.0f);
}

void Camera::update()
{
	viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, 0.0f));
	// viewMatrix = glm::scale(viewMatrix, glm::vec3(zoom, zoom, 1.0f));
}
