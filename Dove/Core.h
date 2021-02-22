#pragma once

#include "SpriteFont.h"
#include "Window.h"
#include "GLSL.h"
#include "Camera.h"
#include "InputManager.h"
#include "FrameManager.h"
#include "Audio.h"
#include "QuadBatch.h"
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
		

		Stage stage{};

	private:
		static Core* core;

		Media media{};
		Window window{};
		Audio audio{};
		SpriteFont sprite_font{};

		GLSL colorProgram;
		Camera camera;
		QuadBatch quad_batch_;
		InputManager input_manager;
		FrameManager frame_manager;
		QuadBatch text_batch;
		

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
		void renderLoop();
	};
}
