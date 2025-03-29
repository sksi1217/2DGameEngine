#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(float newWidth, float newHeight);

	void resize(float newWidth, float newHeight);

	// set
	void setPosition(const glm::vec2 &newPosition);
	void setZoom(float newZoom);

	// get
	const glm::vec2 getPosition() { return position; };
	const float getZoom() { return zoom; };
	const glm::mat4 &getViewMatrix() const { return viewMatrix; }
	const glm::mat4 &getProjectionMatrix() const { return projectionMatrix; }

private:
	Camera();
	Camera(const Camera &) = delete;
	Camera &operator=(const Camera &) = delete;

	void update();

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::vec2 position;
	float zoom;
};

