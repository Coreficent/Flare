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
		glm::vec2 getPosition() const;
		void setScale(float scale);
		float getScale() const;
		glm::mat4 getCameraMatrix() const;
		void update();
		glm::vec2 global_to_local(glm::vec2 global_position);
	private:
		glm::vec2 position;
		glm::mat4 cameraMatrix;
		glm::mat4 orthoMatrix;
		glm::mat4 identityMatrix;
		float scale;
		int window_width;
		int window_height;
		bool updateRequired;
	};
}
