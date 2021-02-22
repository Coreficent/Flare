#pragma once


#include <dove/Quad.h>
#include <dove/GLSL.h>
#include <vector>
#include <dove/Window.h>
#include <dove/Camera.h>
#include <dove/QuadBatch.h>
#include <dove/InputManager.h>
#include <dove/FrameManager.h>
#include <dove/SpriteFont.h>
using namespace std;

class MainGame
{
public:
	MainGame(int windowWdith, int windowHeight);
	~MainGame();

	void run();

private:
	Dove::SpriteFont* sprite_font;
	
	Dove::Window window;
	Dove::GLSL colorProgram;
	Dove::Camera camera;
	Dove::Camera camera_interface;
	Dove::QuadBatch quad_batch_;
	Dove::InputManager input_manager;
	Dove::FrameManager frame_manager;
	Dove::QuadBatch text_batch;

	enum class GameState { running, ended };

	GameState currentState;

	Uint32 currentTicks;
	
	//float timeTracker;


	int windowWidth;
	int windowHeight;

	void initialize();
	void initializeShader();
	void gameLoop();
	void processInput();
	void render();
	void draw_text();
};

