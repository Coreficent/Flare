#include "InputManager.h"

namespace Dove {

	InputManager::InputManager()
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

	bool InputManager::keyPressed(unsigned int keyID)
	{
		auto it = this->keymap.find(keyID);
		return it!=this->keymap.end()?it->second:false;
	}


	
}