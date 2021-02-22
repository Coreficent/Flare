#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Dove
{
	class Camera
	{
	public:
		Camera(int windowWidth, int windowHeight);
		~Camera();
		void setPosition(const glm::vec2& position);
		glm::vec2 getPosition();
		void setScale(float scale);
		float getScale();
		glm::mat4 getCameraMatrix();
		void update();
	private:
		glm::vec2 position;
		glm::mat4 cameraMatrix;
		glm::mat4 orthoMatrix;
		float scale;
		int windowWidth;
		int windowHeight;
		bool updateRequired;
	};

}