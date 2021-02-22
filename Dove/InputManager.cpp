#include "InputManager.h"

namespace Dove
{
	InputManager::InputManager(): keymap{}, mouse_position{0.0f}
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::pressKey(unsigned int keyID)
	{
		this->keymap[keyID] = true;
	}


	void InputManager::releaseKey(unsigned int keyID)
	{
		this->keymap[keyID] = false;
	}

	void InputManager::setMousePosition(float x, float y)
	{
		this->mouse_position.x = x;
		this->mouse_position.y = y;
	}

	glm::vec2 InputManager::get_mouse_position() const
	{
		return this->mouse_position;
	}

	bool InputManager::keyPressed(unsigned int keyID)
	{
		auto it = this->keymap.find(keyID);
		return it != this->keymap.end() ? it->second : false;
	}
}
