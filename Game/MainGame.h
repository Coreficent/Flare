#pragma once


#include <dove/Quad.h>
#include <dove/GLSL.h>
#include <vector>
#include <dove/Window.h>
#include <dove/Camera.h>

using namespace std;

class MainGame
{
public:
	MainGame(int windowWdith, int windowHeight);
	~MainGame();

	void run();
	

private:

	
	

	vector<Dove::Quad*> quads;

	Dove::Window window;
	Dove::GLSL colorProgram;
	Dove::Camera camera;

	enum class GameState { running, ended };

	GameState currentState;

	float timeTracker;
	
	
	float fps;
	unsigned int frameTime;
	unsigned int budget;

	int windowWidth;
	int windowHeight;

	void initialize();
	void initializeShader();
	void gameLoop();
	void processInput();
	void render();
	void calculateFPS();
};

