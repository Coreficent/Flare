#pragma once

#include "SpriteFont.h"
#include "Window.h"
#include "GLSL.h"
#include "Camera.h"
#include "InputManager.h"
#include "FrameManager.h"
#include "Audio.h"
#include "Renderer.h"
#include "Stage.h"
#include "Media.h"


namespace Dove
{
	using namespace std;

	class Core
	{
	public:
		Core(int windowWdith, int windowHeight);
		~Core();

		void run();

		friend class Render;

		friend class Display;


		//Stage stage{};

	private:
		static Core* core;

		Media media{};
		Window window{};
		Audio audio{};


		Renderer quad_batch_;
		InputManager input_manager;
		FrameManager frame_manager;


		enum class GameState
		{
			running,
			ended
		};

		GameState currentState;

		Uint32 currentTicks;

		int windowWidth;
		int windowHeight;


		void gameLoop();
		void processInput();
	};
}
