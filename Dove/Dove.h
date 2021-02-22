#pragma once

#include "SpriteFont.h"
#include "Window.h"
#include "GLSL.h"
#include "Camera.h"
#include "InputManager.h"
#include "FrameManager.h"
#include "AudioEngine.h"
#include "QuadBatch.h"
#include "Stage.h"

namespace Dove {
	using namespace std;

	class Dove
	{
	public:
		Dove(int windowWdith, int windowHeight);
		~Dove();

		void run();

		friend class Display;

	private:
		static Dove* core;

		SpriteFont* sprite_font;

		Window window;
		Stage stage{};
		GLSL colorProgram;
		Camera camera;
		Camera camera_interface;
		QuadBatch quad_batch_;
		InputManager input_manager;
		FrameManager frame_manager;
		QuadBatch text_batch;
		AudioEngine audio_engine;

		enum class GameState { running, ended };

		GameState currentState;

		Uint32 currentTicks;

		int windowWidth;
		int windowHeight;

		void initialize();
		void initializeShader();
		void gameLoop();
		void processInput();
		void render();

	};

}
