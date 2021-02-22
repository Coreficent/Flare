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
#include "Render.h"

namespace Dove
{
	using namespace std;

	class Dove
	{
	public:
		Dove(int windowWdith, int windowHeight);
		~Dove();

		void run();

		friend class Display;

		Stage stage{};

	private:
		static Dove* core;

		Media media{};
		Window window{};
		Render render{};
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

		void initializeShader();
		void gameLoop();
		void processInput();
		void renderLoop();
	};
}
