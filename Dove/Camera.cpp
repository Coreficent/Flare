#include "Camera.h"
namespace Dove
{


	Camera::Camera(int windowWidth, int windowHeight) :position{ 0.0f,0.0f }, cameraMatrix(1.0f), orthoMatrix{ glm::ortho(0.0f,static_cast<float>(windowWidth),0.0f,static_cast<float>(windowHeight)) }, scale{ 1.0f }, windowWidth{ windowWidth }, windowHeight{ windowHeight }, updateRequired{ true }
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

	glm::vec2 Camera::getPosition()
	{
		return this->position;
	}

	void Camera::setScale(float scale)
	{
		this->scale = scale;
		this->updateRequired = true;
	}

	float Camera::getScale()
	{
		return this->scale;
	}

	glm::mat4 Camera::getCameraMatrix()
	{
		return this->cameraMatrix;
	}

	void Camera::update()
	{
		if (this->updateRequired)
		{
			glm::vec3 translate{ -this->position.x + this->windowWidth/2, -this->position.y+this->windowHeight/2, 0.0f };
			this->cameraMatrix = glm::translate(this->orthoMatrix, translate);

			glm::vec3 scale{ this->scale,this->scale,0.0f };
			this->cameraMatrix = glm::scale(glm::mat4(1.0f), scale)*this->cameraMatrix;

			this->updateRequired = false;
		}
	}
}