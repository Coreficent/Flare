#pragma once
#include <unordered_map>
#include <glm/detail/type_vec2.hpp>

namespace Dove
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		bool keyPressed(unsigned int keyID);

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);
		void setMousePosition(float x, float y);
		glm::vec2 get_mouse_position() const;
	private:
		std::unordered_map<unsigned int, bool> keymap;
		glm::vec2 mouse_position;
	};
}
