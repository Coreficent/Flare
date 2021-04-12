#include "Camera.h"

namespace Flare
{
	Camera::Camera(int window_width, int window_height)
		: position{0.0f,0.0f}, cameraMatrix(1.0f), orthoMatrix{glm::ortho(0.0f, static_cast<float>(window_width), static_cast<float>(window_height), 0.0f)}, identityMatrix{1.0f}, scale{1.0f}, window_width{window_width}, window_height{window_height}, updateRequired{true}
	{
	}


	Camera::~Camera()
	{
	}

	void Camera::setPosition(const glm::vec2& position)
	{
		this->position = position;
		this->updateRequired = true;
	}

	glm::vec2 Camera::getPosition() const
	{
		return this->position;
	}

	void Camera::setScale(float scale)
	{
		this->scale = scale;
		this->updateRequired = true;
	}

	float Camera::getScale() const
	{
		return this->scale;
	}

	glm::mat4 Camera::getCameraMatrix() const
	{
		return this->cameraMatrix;
	}

	void Camera::update()
	{
		if (this->updateRequired)
		{
			glm::vec3 translate{this->position.x + this->window_width / 2, this->position.y + this->window_height / 2, 0.0f};
			this->cameraMatrix = glm::translate(this->orthoMatrix, translate);
			glm::vec3 scale{this->scale,this->scale,0.0f};
			this->cameraMatrix = glm::scale(this->identityMatrix, scale) * this->cameraMatrix;
			this->updateRequired = false;
		}
	}

	glm::vec2 Camera::global_to_local(glm::vec2 global_position) const
	{
		global_position -= glm::vec2(this->window_width / 2, this->window_height / 2);
		global_position /= this->scale;
		global_position += this->position;
		return global_position;
	}
}
