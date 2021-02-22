#pragma once


#include <dove/Quad.h>
#include <dove/GLSL.h>
#include <vector>
#include <dove/Window.h>
#include <dove/Camera.h>
#include <dove/QuadBatch.h>
#include <dove/InputManager.h>
#include <dove/FrameManager.h>
using namespace std;

class MainGame
{
public:
	MainGame(int windowWdith, int windowHeight);
	~MainGame();

	void run();
	

private:

	
	


	Dove::Window window;
	Dove::GLSL colorProgram;
	Dove::Camera camera;
	Dove::QuadBatch quad_batch_;
	Dove::InputManager input_manager;
	Dove::FrameManager frame_manager;


	enum class GameState { running, ended };

	GameState currentState;

	Uint32 currentTicks;
	
	float timeTracker;


	int windowWidth;
	int windowHeight;

	void initialize();
	void initializeShader();
	void gameLoop();
	void processInput();
	void render();

};

