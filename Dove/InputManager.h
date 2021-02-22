#pragma once
#include <unordered_map>

namespace Dove {

	class InputManager
	{
	public:
		InputManager();
		~InputManager();
		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);
		bool keyPressed(unsigned int keyID);
	private:
		std::unordered_map<unsigned int, bool> keymap;
	};

}
